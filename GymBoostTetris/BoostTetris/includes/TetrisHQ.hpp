#ifdef WIN32
#define API extern "C" __declspec(dllexport)
#else
#define API extern "C"
#endif

#include <cstdint>
#include <cstddef>

struct BlockDatas {
    struct BlockData {
        uint8_t r0[4];
        uint8_t r1[4];
        uint8_t r2[4];
        uint8_t r3[4];
    };
    BlockData b0;
    BlockData b1;
    BlockData b2;
    BlockData b3;
};

struct Block {

    enum Type : int8_t {
        NONE = -1,
        Z = 0, L, O, S, I, J, T,
        LENGTH
    } type;
    int width, height;

    Block(Type type, int width, int height, BlockDatas data);

    uint8_t data[4][4][4];
};

struct State {
    uint8_t board[32][18];
    bool game_state;
    Block::Type next[14];
    Block::Type hold;
    bool has_holded;
    Block::Type current;
    int8_t rot;
    int x, y;
    int clean_count;
};

API void sseed(uint32_t seed);

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

API void* function_table();
