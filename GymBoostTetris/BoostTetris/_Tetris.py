from .. import DynamicLibrary as dl
from ._Structures import FunctionTable
import ctypes
import os

current_dir = os.path.dirname(__file__)

Kernel = dl.DynamicLibrary(temp_lib='TetrisKernel', temp_dir=os.path.join(current_dir, 'temp'))
Kernel.compile_file(os.path.join(current_dir, 'includes/Tetris.cpp'), {
    'sseed'        : { 'argtypes': [dl.void_p, dl.uint32], 'restype': dl.void },
    
    'reset'        : { 'argtypes': [dl.void_p], 'restype': dl.void },
    'generateBlock': { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'moveLeft'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'moveRight'    : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'softDrop'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'hardDrop'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'rotateLeft'   : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'rotateRight'  : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'hold'         : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    
    'moveBlock'    : { 'argtypes': [dl.void_p, dl.int32, dl.int32, dl.int8], 'restype': dl.bool },
    
    'toString'     : { 'argtypes': [dl.void_p, dl.uint8_p, dl.uint64], 'restype': dl.void },

    'eraseCurrent' : { 'argtypes': [dl.void_p], 'restype': dl.void },
    'pasteCurrent' : { 'argtypes': [dl.void_p], 'restype': dl.void },

    'initialize'   : { 'argtypes': [], 'restype': dl.void },
    
    'function_table': { 'argtypes': [], 'restype': dl.void_p },
})
Kernel.initialize()

FTable = FunctionTable.from_address(Kernel.function_table())

KernelHQ = dl.DynamicLibrary(temp_lib='TetrisHQKernel', temp_dir=os.path.join(current_dir, 'temp'))
KernelHQ.compile_file(os.path.join(current_dir, 'includes/TetrisHQ.cpp'), {
    'sseed'        : { 'argtypes': [dl.uint32], 'restype': dl.void },
    
    'reset'        : { 'argtypes': [dl.void_p], 'restype': dl.void },
    'generateBlock': { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'moveLeft'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'moveRight'    : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'softDrop'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'hardDrop'     : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'rotateLeft'   : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'rotateRight'  : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    'hold'         : { 'argtypes': [dl.void_p], 'restype': dl.bool },
    
    'moveBlock'    : { 'argtypes': [dl.void_p, dl.int32, dl.int32, dl.int8], 'restype': dl.bool },
    
    'toString'     : { 'argtypes': [dl.void_p, dl.uint8_p, dl.uint64], 'restype': dl.void },

    'eraseCurrent' : { 'argtypes': [dl.void_p], 'restype': dl.void },
    'pasteCurrent' : { 'argtypes': [dl.void_p], 'restype': dl.void },

    'initialize'   : { 'argtypes': [], 'restype': dl.void },
    
    'function_table': { 'argtypes': [], 'restype': dl.void_p },
})
KernelHQ.initialize()

FTableHQ = FunctionTable.from_address(KernelHQ.function_table())
