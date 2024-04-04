#ifdef WIN32
#define API extern "C" __declspec(dllexport)
#else
#define API extern "C"
#endif

#include <cstdint>
#include <cstddef>

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
    int srs_index;
};

API void sseed(State* state, uint32_t seed);

API void reset(State* state);
API bool generateBlock(State* state);

API bool moveLeft(State* state);
API bool moveRight(State* state);
API bool softDrop(State* state);
API bool hardDrop(State* state);
API bool rotateLeft(State* state);
API bool rotateRight(State* state);
// API bool rotate180(State* state);
API bool hold(State* state);

API bool moveBlock(State* state, int x, int y, int8_t rot);

API void toString(State* state, char* buf, size_t size);

API void eraseCurrent(State* state);
API void pasteCurrent(State* state);

API void initialize();

API const Block(*block_data())[7][4];
API void* function_table();
