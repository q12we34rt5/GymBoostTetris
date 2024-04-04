#!python3

# BoostTetris is a Python wrapper for the C++ Tetris library
# The C++ source code will be compiled into a shared library during the runtime
#
# BoostTetris.Kernel:
#   A DynamicLibrary object that wraps the BoostTetris/include/Tetris.hpp and .cpp
#   This version is optimized for speed
#
# BoostTetris.KernelHQ:
#   A DynamicLibrary object that wraps the BoostTetris/include/TetrisHQ.hpp and .cpp
#   This version has almost the same functionality as Kernel, but the board records more information of the tetrominoes

from GymBoostTetris import BoostTetris as BT
from random import randint
import ctypes
import time
from os import system

# Try to use the different versions of the BoostTetris library and see the difference
TetrisKernel = [BT.Kernel, BT.KernelHQ][0]
TetrisState  = [BT.State , BT.StateHQ ][0]

action_functions = [
    TetrisKernel.moveLeft,
    TetrisKernel.moveRight,
    TetrisKernel.softDrop,
    TetrisKernel.hardDrop,
    TetrisKernel.rotateLeft,
    TetrisKernel.rotateRight,
    TetrisKernel.hold
]

buffer = bytearray(1000)
def toString(state_ptr):
    TetrisKernel.toString(state_ptr, buffer, len(buffer))
    return buffer.decode('utf-8')

def reset(state_ptr):
    TetrisKernel.reset(state_ptr)
    # Must call generateBlock after reset
    TetrisKernel.generateBlock(state_ptr)

# Create a C++ struct instance in Python
state = TetrisState()
state_ptr = ctypes.addressof(state)

system('clear')
reset(state_ptr)
# Game loop
while state.game_state:
    # Randomly select an action
    act_func = action_functions[randint(0, len(action_functions) - 1)]
    act_func(state_ptr)
    # Do soft-drop in every step
    TetrisKernel.softDrop(state_ptr)
    # Print the state
    print('\033[1;1H' + toString(state_ptr))
    # Wait for a while
    time.sleep(0.1)
