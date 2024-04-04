#!python3

# This example demonstrates how to use the BoostTetris library with a dynamic library
# The game loop does the same thing as the example/boost_tetris_example.py but implemented in C++

from GymBoostTetris import BoostTetris as BT
from GymBoostTetris import DynamicLibrary as dl
import ctypes
from os import system
import os

current_dir = os.path.dirname(__file__)

lib = dl.DynamicLibrary(temp_lib='TetrisLibrary', temp_dir=os.path.join(current_dir, 'temp'))
lib.compile_string(r'''
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <thread>

struct Block {
    enum Type : int8_t {
        NONE = -1,
        Z = 0, L, O, S, I, J, T,
        LENGTH
    };
    uint32_t data[4];
};

struct State {
    uint32_t board[32];
    bool game_state;
    Block::Type next[14];
    Block::Type hold;
    bool has_holded;
    Block::Type current;
    int8_t rot;
    int x, y;
    int clean_count;
    int life_time;
    uint32_t seed;
};

struct FunctionTable {
    void (*reset        )(State* state);
    bool (*generateBlock)(State* state);
    bool (*moveLeft     )(State* state);
    bool (*moveRight    )(State* state);
    bool (*softDrop     )(State* state);
    bool (*hardDrop     )(State* state);
    bool (*rotateLeft   )(State* state);
    bool (*rotateRight  )(State* state);
    bool (*hold         )(State* state);
    bool (*moveBlock    )(State* state, int x, int y, int8_t rot);
    void (*toString     )(State* state, char* buf, size_t size);
    void (*eraseCurrent )(State* state);
    void (*pasteCurrent )(State* state);
    const Block(*(*block_data)())[7][4];
} *ft;

using ActionCallback = bool(*)(State*);

ActionCallback action_callbacks[7];

API void init_globals(void* ft) {
    ::ft = reinterpret_cast<FunctionTable*>(ft);
    action_callbacks[0] = ::ft->moveLeft;
    action_callbacks[1] = ::ft->moveRight;
    action_callbacks[2] = ::ft->softDrop;
    action_callbacks[3] = ::ft->hardDrop;
    action_callbacks[4] = ::ft->rotateLeft;
    action_callbacks[5] = ::ft->rotateRight;
    action_callbacks[6] = ::ft->hold;
}

enum class Action : int {
    NONE = -1,
    LEFT = 0,
    RIGHT,
    SOFT_DROP,
    HARD_DROP,
    ROT_LEFT,
    ROT_RIGHT,
    HOLD,
};

API void randomGame(State* state) {
    ft->reset(state);
    ft->generateBlock(state);

    // Game loop
    while (state->game_state) {
        // Randomly select an action
        action_callbacks[rand() % 7](state);

        // Do soft-drop in every step
        ft->softDrop(state);

        // Print the state
        static char buffer[1000];
        ft->toString(state, buffer, sizeof(buffer));
        puts("\033[1;1H");
        puts(buffer);

        // Wait for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
''', {
    'init_globals'  : { 'argtypes': [dl.void_p], 'restype': dl.void },
    'randomGame'    : { 'argtypes': [dl.void_p], 'restype': dl.void },
})
lib.init_globals(BT.Kernel.function_table())

state = BT.State()
state_ptr = ctypes.addressof(state)

system('clear')
lib.randomGame(state_ptr)
