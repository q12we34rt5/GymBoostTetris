import platform
import os
import subprocess
import ctypes
from ._types import void

system = platform.system()

class CompileError(Exception):
    pass

class FunctionWrapper:
    
    def __init__(self, name, args, ret, callback):
        self.name = name
        self.args = args
        self.ret  = ret
        self.callback = callback
    
    def __call__(self, *args):
        return self.callback(*(m(arg) for m, arg in zip(self.args, args)))
    
    def __repr__(self):
        args = f'({self.args[0]})' if len(self.args) == 1 else tuple(self.args)
        return f'{self.ret} {self.name}{args}'

extractor_fmt = r'''void* __get_library_function_pointer_%s() { return reinterpret_cast<void*>(%s); }'''
fptr_extract = r'''
#ifdef WIN32
%s
#else
%s
#endif
'''
def create_extractor(func_names):
    win32 = '\n'.join(['extern "C" __declspec(dllexport) ' + extractor_fmt % (func, func) for func in func_names])
    linux = '\n'.join(['extern "C" ' + extractor_fmt % (func, func) for func in func_names])
    return fptr_extract % (win32, linux)

class DynamicLibrary:
    
    def __init__(self, cc_path='g++', temp_dir='temp', temp_src='lib.cpp',
        temp_lib='lib'):
        self.cc_path = cc_path
        self.temp_dir = temp_dir
        self.temp_src = temp_src
        self.temp_lib = f'{temp_lib}.dll' if system == 'Windows' else f'{temp_lib}.so'
        os.makedirs(self.temp_dir, exist_ok=True)
        self.lib = None
        self.rec_functions = []
        if system != 'Windows':
            self._dlclose_func = ctypes.cdll.LoadLibrary('').dlclose
            self._dlclose_func.argtypes = [ctypes.c_void_p]
    
    def __del__(self):
        self.close_library()
    
    def _create_file(self, text):
        path = self.temp_dir
        file = self.temp_src
        with open(os.path.join(path, file), "w") as out:
            out.write(text)

    def _compile_library(self, src=None):
        cc      = self.cc_path
        path    = self.temp_dir
        file    = self.temp_src
        src     = src if src else os.path.join(path, file)
        target  = os.path.join(path, self.temp_lib)
        command = [cc, src, '-shared', '-o', target, '-O3', '-g']
        if system != 'Windows':
            command.append('-fPIC')
        subproc = subprocess.run(command, capture_output=True)
        if subproc.stderr.decode():
            raise CompileError('\n' + subproc.stderr.decode())
        self.target = target
    
    def _parse_function(self, functions):
        for key in functions:
            dll_func = getattr(self.lib, key)
            func_info = functions[key]
            
            args = func_info.setdefault('argtypes', [])
            ret  = func_info.setdefault('restype', void)
            setattr(self, key, FunctionWrapper(key, args, ret, dll_func))
            self.rec_functions.append(key)
            
            if 'argtypes' in func_info:
                argtypes = func_info['argtypes']
                dll_func.argtypes = [ty.type_mapping for ty in argtypes]
            if 'restype' in func_info:
                dll_func.restype = func_info['restype'].type_mapping

    def compile_string(self, source, functions={}, prefix=r'''
#ifdef WIN32
#define API extern "C" __declspec(dllexport)
#else
#define API extern "C"
#endif
'''):
        self.close_library()
        self._create_file(prefix + source + create_extractor(functions.keys()))
        self._compile_library()
        path   = self.temp_dir
        target = os.path.join(path, self.temp_lib)
        self.lib = ctypes.CDLL(target)
        self._parse_function(functions)
        # get function pointer
        for func in functions.keys():
            extractor = getattr(self.lib, '__get_library_function_pointer_%s' % func)
            extractor.restype = ctypes.c_void_p
            getattr(self, func).address = extractor()
    
    def compile_file(self, path, functions={}):
        self.close_library()
        self._compile_library(path)
        path   = self.temp_dir
        target = os.path.join(path, self.temp_lib)
        self.lib = ctypes.CDLL(target)
        self._parse_function(functions)

    def close_library(self):
        for key in self.rec_functions:
            delattr(self, key)
        self.rec_functions = []
        if self.lib == None:
            return
        if system == 'Windows':
            ctypes.windll.kernel32.FreeLibrary(self.lib._handle)
        else:
            self._dlclose_func(self.lib._handle)
        self.lib = None
        os.remove(self.target)
