#include "Tetris.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include <cassert>

#define __SPEEDUP__

const Block blocks[7][4] = {{
    {0b11110000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00001100000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b11000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}},
{   {0b00001100000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b11000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b11110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}},
{   {0b00111100000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00111100000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00111100000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00111100000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}},
{   {0b00111100000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00001100000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b11000000000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}},
{   {0b00000000000000000000000000000000ull,
     0b11111111000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00001100000000000000000000000000ull,
     0b00001100000000000000000000000000ull,
     0b00001100000000000000000000000000ull,
     0b00001100000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b11111111000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull}},
{   {0b11000000000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00111100000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b00001100000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}},
{   {0b00110000000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b00000000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b00111100000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00000000000000000000000000000000ull,
     0b11111100000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull},
    {0b00110000000000000000000000000000ull,
     0b11110000000000000000000000000000ull,
     0b00110000000000000000000000000000ull,
     0b00000000000000000000000000000000ull}}
};

template<template<int...> class Container, int n, int ...args>
struct IndexGenerator : IndexGenerator<Container, n - 1, n - 1, args...> {};
template<template<int...> class Container, int ...args>
struct IndexGenerator<Container, 0, args...> { using result = Container<args...>; };
template<int ...args>
struct Wrapper {
    template<int height, int padding, uint32_t row, uint32_t wall>
    struct BoardInitializer {
        template<bool condition, typename x> struct If {};
        template<typename x> struct If<true, x> { static constexpr uint32_t value = wall; };
        template<typename x> struct If<false, x> { static constexpr uint32_t value = row; };

        static const uint32_t board[height];
    };
};
template<int ...args>
template<int height, int padding, uint32_t row, uint32_t wall>
const uint32_t Wrapper<args...>::BoardInitializer<height, padding, row, wall>::board[height] = {
    Wrapper<args...>::BoardInitializer<height, padding, row, wall>::If<(/*args < padding || */args >= height - padding), int>::value...
};

struct SRS {
    struct Coordinate { int x, y; };
    const Coordinate* test[4][2];
    int length;
    SRS(Block::Type type);
};

SRS::SRS(Block::Type type) : test{}, length(-1) {
    static const SRS::Coordinate JLSTZ[4][2][5] = {{
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},  // 0 >> 1
            {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}      // 0 >> 3
        }, {
            {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},      // 1 >> 2
            {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}       // 1 >> 0
        }, {
            {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // 2 >> 3
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}   // 2 >> 1
        }, {
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},   // 3 >> 0
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}    // 3 >> 2
        }
    };
    static const SRS::Coordinate I[4][2][5] = {{
            {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},    // 0 >> 1
            {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}     // 0 >> 3
        }, {
            {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},    // 1 >> 2
            {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}}     // 1 >> 0
        }, {
            {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},    // 2 >> 3
            {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}     // 2 >> 1
        }, {
            {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},    // 3 >> 0
            {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}     // 3 >> 2
        }
    };
    static const SRS::Coordinate O[4][2][1] = {{
            {{0, 0}},                                       // 0 >> 1
            {{0, 0}}                                        // 0 >> 3
        }, {
            {{0, 0}},                                       // 1 >> 2
            {{0, 0}}                                        // 1 >> 0
        }, {
            {{0, 0}},                                       // 2 >> 3
            {{0, 0}}                                        // 2 >> 1
        }, {
            {{0, 0}},                                       // 3 >> 0
            {{0, 0}}                                        // 3 >> 2
        }
    };
    switch (type) {
    case Block::Type::J:
    case Block::Type::L:
    case Block::Type::S:
    case Block::Type::T:
    case Block::Type::Z:
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 2; j++)
                test[i][j] = JLSTZ[i][j];
        length = 5;
        break;
    case Block::Type::I:
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 2; j++)
                test[i][j] = I[i][j];
        length = 5;
        break;
    case Block::Type::O:
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 2; j++)
                test[i][j] = O[i][j];
        length = 1;
        break;
    default:
        break;
    }
}

static const SRS srs[Block::Type::LENGTH] = {
    Block::Type::Z,
    Block::Type::L,
    Block::Type::O,
    Block::Type::S,
    Block::Type::I,
    Block::Type::J,
    Block::Type::T
};

#define              BOARD_HEIGHT   32
#define              BOARD_PADDING  4
static constexpr int BOARD_TOP    = BOARD_HEIGHT - BOARD_PADDING - 21;
static constexpr int BOARD_BOTTOM = BOARD_TOP + 20;
static constexpr int BOARD_LEFT   = 3;

// static uint32_t seed = 123456789;

// void sseed(uint32_t seed) {
//     ::seed = seed;
// }

static uint32_t xorshf32(uint32_t& seed) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

#ifdef __SPEEDUP__

struct compact_memory {
    unsigned b0 : 3;
    unsigned b1 : 3;
    unsigned b2 : 3;
    unsigned b3 : 3;
    unsigned b4 : 3;
    unsigned b5 : 3;
    unsigned b6 : 3;
};

//static Block::Type next_block_permutations[5040][7];
static compact_memory next_block_permutations[5040];
static clock_t next_block_permutations_initializer() {
    clock_t start, end;
    start = clock();

    //next_block_permutations = new Block::Type[5040][7];
    Block::Type next[] = { Block::Z, Block::L, Block::O, Block::S, Block::I, Block::J, Block::T };
    int index = 0;
    do {
        //memcpy(&next_block_permutations[index++], next, sizeof(next));
        compact_memory& ref = next_block_permutations[index++];
        ref.b0 = unsigned(next[0]);
        ref.b1 = unsigned(next[1]);
        ref.b2 = unsigned(next[2]);
        ref.b3 = unsigned(next[3]);
        ref.b4 = unsigned(next[4]);
        ref.b5 = unsigned(next[5]);
        ref.b6 = unsigned(next[6]);
    } while (std::next_permutation(next, next + 7));

    end = clock();
    return end - start;
}
//static const clock_t next_block_permutations_initialize_cost_time = next_block_permutations_initializer();

static inline void randomBlocks(Block::Type dest[], uint32_t& seed) {
    //memcpy(dest, next_block_permutations[xorshf32() % 5040], sizeof(int8_t) * 7);
    compact_memory& ref = next_block_permutations[xorshf32(seed) % 5040];
    dest[0] = Block::Type(ref.b0);
    dest[1] = Block::Type(ref.b1);
    dest[2] = Block::Type(ref.b2);
    dest[3] = Block::Type(ref.b3);
    dest[4] = Block::Type(ref.b4);
    dest[5] = Block::Type(ref.b5);
    dest[6] = Block::Type(ref.b6);
}

#else

static inline void randomBlocks(Block::Type dest[], uint32_t& seed) {
    static const Block::Type init[] = { Block::Z, Block::L, Block::O, Block::S, Block::I, Block::J, Block::T };
    memcpy(dest, init, sizeof(int8_t) * 7);
    for (int i = 0; i < 7; i++) {
        uint32_t rnd = xorshf32(seed) % 7;
        Block::Type temp = dest[i];
        dest[i] = dest[rnd];
        dest[rnd] = temp;
    }
    for (int i = 0; i < 7; i++) {
        uint32_t rnd = xorshf32(seed) % 7;
        Block::Type temp = dest[i];
        dest[i] = dest[rnd];
        dest[rnd] = temp;
    }
}

#endif

inline static void clean(State* state) {
    using Initializer = IndexGenerator<Wrapper, BOARD_HEIGHT>::result::BoardInitializer<BOARD_HEIGHT, BOARD_PADDING,
        0b11111100000000000000000000111111u,  // row data
        0b11111111111111111111111111111111u>; // wall data
    memcpy(state->board, Initializer::board, sizeof(int32_t) * BOARD_HEIGHT);
}

inline int cleanLines(State* state) {
    static constexpr uint32_t fullfilled = 0b00000001010101010101010101000000u;
    int count = 0;
    for (int i = BOARD_BOTTOM; i >= BOARD_TOP; i--) {
        while ((state->board[i - count] & fullfilled) == fullfilled) {
            state->board[i - count] = 0b11111100000000000000000000111111u;
            count++;
        }
        state->board[i] = state->board[i - count];
    }
    return count;
}

void sseed(State* state, uint32_t seed) {
    state->seed = seed;
}

void reset(State* state) {
    clean(state);
    state->game_state = true;
    randomBlocks(state->next, state->seed);
    randomBlocks(state->next + 7, state->seed);
    state->hold = Block::NONE;
    state->has_holded = false;
    state->current = Block::NONE;
    state->rot = 0;
    state->x = -1;
    state->y = -1;
    state->clean_count = 0;
    state->life_time = 0;
    state->srs_index = -1;
}

bool generateBlock(State* state) {
    int line_count = cleanLines(state);
    state->clean_count += line_count;

    state->has_holded = false;
    state->srs_index = 0;

    Block::Type cur = state->next[0];
    state->x = BOARD_LEFT + 3;
    state->y = 0;
    state->rot = 0;

    auto& ref_block_data = blocks[cur][0].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    const uint32_t block_r1 = ref_block_data[0] >> x_offset;
    const uint32_t block_r2 = ref_block_data[1] >> x_offset;
    const uint32_t block_r3 = ref_block_data[2] >> x_offset;
    const uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    // test collision
    const bool collision = (block_r1 & board_r1) | (block_r2 & board_r2) | (block_r3 & board_r3) | (block_r4 & board_r4);

    if (collision) {
        state->game_state = false;
        return false;
    }

    state->current = cur;

    board_r1 |= block_r1;
    board_r2 |= block_r2;
    board_r3 |= block_r3;
    board_r4 |= block_r4;

    // shift the next blocks
    for (int i = 0; i < 13; i++)
        state->next[i] = state->next[i + 1];
    state->next[13] = Block::NONE;

    // generate new random blocks if needed
    if (state->next[7] == Block::NONE) {
        randomBlocks(state->next + 7, state->seed);
    }

    return true;
}

bool moveLeft(State* state) {
    const int test_x = state->x - 1;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = test_x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    board_r1 ^= board_r1 & (block_r1 >> 2);
    board_r2 ^= board_r2 & (block_r2 >> 2);
    board_r3 ^= board_r3 & (block_r3 >> 2);
    board_r4 ^= board_r4 & (block_r4 >> 2);

    // test collision
    const bool collision = (block_r1 & board_r1) | (block_r2 & board_r2) | (block_r3 & board_r3) | (block_r4 & board_r4);

    state->x = collision * state->x + !collision * test_x;

    board_r1 |= collision * (block_r1 >> 2) + !collision * block_r1;
    board_r2 |= collision * (block_r2 >> 2) + !collision * block_r2;
    board_r3 |= collision * (block_r3 >> 2) + !collision * block_r3;
    board_r4 |= collision * (block_r4 >> 2) + !collision * block_r4;

    return !collision;
}
bool moveRight(State* state) {
    const int test_x = state->x + 1;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = test_x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    board_r1 ^= board_r1 & (block_r1 << 2);
    board_r2 ^= board_r2 & (block_r2 << 2);
    board_r3 ^= board_r3 & (block_r3 << 2);
    board_r4 ^= board_r4 & (block_r4 << 2);

    // test collision
    const bool collision = (block_r1 & board_r1) | (block_r2 & board_r2) | (block_r3 & board_r3) | (block_r4 & board_r4);

    state->x = collision * state->x + !collision * test_x;

    board_r1 |= collision * (block_r1 << 2) + !collision * block_r1;
    board_r2 |= collision * (block_r2 << 2) + !collision * block_r2;
    board_r3 |= collision * (block_r3 << 2) + !collision * block_r3;
    board_r4 |= collision * (block_r4 << 2) + !collision * block_r4;

    return !collision;
}
bool softDrop(State* state) {
    const int test_y = state->y + 1;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];
    uint32_t& board_r5 = state->board[y_offset + 4];

    board_r1 ^= board_r1 & block_r1;
    board_r2 ^= board_r2 & block_r2;
    board_r3 ^= board_r3 & block_r3;
    board_r4 ^= board_r4 & block_r4;

    // test collision
    const bool collision = (block_r1 & board_r2) | (block_r2 & board_r3) | (block_r3 & board_r4) | (block_r4 & board_r5);

    state->y = collision * state->y + !collision * test_y;
    assert(state->y < 32);

    board_r1 |= collision * block_r1 + !collision * board_r1;
    //                                              ~~~~~
    board_r2 |= collision * block_r2 + !collision * block_r1;
    board_r3 |= collision * block_r3 + !collision * block_r2;
    board_r4 |= collision * block_r4 + !collision * block_r3;
    board_r5 |= collision * board_r5 + !collision * block_r4;
    //                      ~~~~~

    return !collision;
}
bool hardDrop(State* state) {
    while (softDrop(state));
    return generateBlock(state);
}
bool rotateLeft(State* state) {
    const int8_t test_rot = (state->rot + 3) % 4;
    // get wall kick tests
    auto& srs_rot_tests = srs[state->current].test[state->rot][1];
    auto& rot_tests_len = srs[state->current].length;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    board_r1 ^= board_r1 & block_r1;
    board_r2 ^= board_r2 & block_r2;
    board_r3 ^= board_r3 & block_r3;
    board_r4 ^= board_r4 & block_r4;

    auto& ref_rot_block_data = blocks[state->current][test_rot].data;
    for (int i = 0; i < rot_tests_len; i++) {
        const int srs_x_offset = srs_rot_tests[i].x;
        const int srs_y_offset = srs_rot_tests[i].y;
        const int test_x_offset = x_offset + (srs_x_offset << 1);
        const int test_y_offset = y_offset - srs_y_offset;
        uint32_t test_block_r1 = ref_rot_block_data[0] >> test_x_offset;
        uint32_t test_block_r2 = ref_rot_block_data[1] >> test_x_offset;
        uint32_t test_block_r3 = ref_rot_block_data[2] >> test_x_offset;
        uint32_t test_block_r4 = ref_rot_block_data[3] >> test_x_offset;
        uint32_t& test_board_r1 = state->board[test_y_offset + 0];
        uint32_t& test_board_r2 = state->board[test_y_offset + 1];
        uint32_t& test_board_r3 = state->board[test_y_offset + 2];
        uint32_t& test_board_r4 = state->board[test_y_offset + 3];
        // test collision
        const bool collision
            = (test_block_r1 & test_board_r1)
            | (test_block_r2 & test_board_r2)
            | (test_block_r3 & test_board_r3)
            | (test_block_r4 & test_board_r4);
        if (!collision) {
            state->rot = test_rot;
            state->x += srs_x_offset;
            state->y -= srs_y_offset;
            test_board_r1 |= test_block_r1;
            test_board_r2 |= test_block_r2;
            test_board_r3 |= test_block_r3;
            test_board_r4 |= test_block_r4;
            state->srs_index = i;
            return true;
        }
    }

    board_r1 |= block_r1;
    board_r2 |= block_r2;
    board_r3 |= block_r3;
    board_r4 |= block_r4;

    return false;
}
bool rotateRight(State* state) {
    const int8_t test_rot = (state->rot + 1) % 4;
    // get wall kick tests
    auto& srs_rot_tests = srs[state->current].test[state->rot][0];
    auto& rot_tests_len = srs[state->current].length;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    board_r1 ^= board_r1 & block_r1;
    board_r2 ^= board_r2 & block_r2;
    board_r3 ^= board_r3 & block_r3;
    board_r4 ^= board_r4 & block_r4;

    auto& ref_rot_block_data = blocks[state->current][test_rot].data;
    for (int i = 0; i < rot_tests_len; i++) {
        const int srs_x_offset = srs_rot_tests[i].x;
        const int srs_y_offset = srs_rot_tests[i].y;
        const int test_x_offset = x_offset + (srs_x_offset << 1);
        const int test_y_offset = y_offset - srs_y_offset;
        uint32_t test_block_r1 = ref_rot_block_data[0] >> test_x_offset;
        uint32_t test_block_r2 = ref_rot_block_data[1] >> test_x_offset;
        uint32_t test_block_r3 = ref_rot_block_data[2] >> test_x_offset;
        uint32_t test_block_r4 = ref_rot_block_data[3] >> test_x_offset;
        uint32_t& test_board_r1 = state->board[test_y_offset + 0];
        uint32_t& test_board_r2 = state->board[test_y_offset + 1];
        uint32_t& test_board_r3 = state->board[test_y_offset + 2];
        uint32_t& test_board_r4 = state->board[test_y_offset + 3];
        // test collision
        const bool collision
            = (test_block_r1 & test_board_r1)
            | (test_block_r2 & test_board_r2)
            | (test_block_r3 & test_board_r3)
            | (test_block_r4 & test_board_r4);
        if (!collision) {
            state->rot = test_rot;
            state->x += srs_x_offset;
            state->y -= srs_y_offset;
            test_board_r1 |= test_block_r1;
            test_board_r2 |= test_block_r2;
            test_board_r3 |= test_block_r3;
            test_board_r4 |= test_block_r4;
            state->srs_index = i;
            return true;
        }
    }

    board_r1 |= block_r1;
    board_r2 |= block_r2;
    board_r3 |= block_r3;
    board_r4 |= block_r4;

    return false;
}
// bool rotate180(State* state);
bool hold(State* state) {
    if (state->has_holded)
        return false;
    
    if (state->hold != Block::NONE) {
        // push the holded block to the block queue
        for (int i = 13; i > 0; i--)
            state->next[i] = state->next[i - 1];
        state->next[0] = state->hold;
    }
    state->hold = state->current;

    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];

    board_r1 ^= board_r1 & (ref_block_data[0] >> x_offset);
    board_r2 ^= board_r2 & (ref_block_data[1] >> x_offset);
    board_r3 ^= board_r3 & (ref_block_data[2] >> x_offset);
    board_r4 ^= board_r4 & (ref_block_data[3] >> x_offset);

    generateBlock(state);

    state->has_holded = true;
    return true;
}

bool moveBlock(State* state, int x, int y, int8_t rot) {
    x += 2;
    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t block_r1 = ref_block_data[0] >> x_offset;
    uint32_t block_r2 = ref_block_data[1] >> x_offset;
    uint32_t block_r3 = ref_block_data[2] >> x_offset;
    uint32_t block_r4 = ref_block_data[3] >> x_offset;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];
    // erase
    board_r1 ^= board_r1 & block_r1;
    board_r2 ^= board_r2 & block_r2;
    board_r3 ^= board_r3 & block_r3;
    board_r4 ^= board_r4 & block_r4;
    // test
    auto& ref_test_block_data = blocks[state->current][rot].data;
    const int x_test_offset = x << 1;
    const int y_test_offset = BOARD_TOP + y;
    uint32_t test_block_r1 = ref_test_block_data[0] >> x_test_offset;
    uint32_t test_block_r2 = ref_test_block_data[1] >> x_test_offset;
    uint32_t test_block_r3 = ref_test_block_data[2] >> x_test_offset;
    uint32_t test_block_r4 = ref_test_block_data[3] >> x_test_offset;
    uint32_t& test_board_r1 = state->board[y_test_offset + 0];
    uint32_t& test_board_r2 = state->board[y_test_offset + 1];
    uint32_t& test_board_r3 = state->board[y_test_offset + 2];
    uint32_t& test_board_r4 = state->board[y_test_offset + 3];
    // test collision
    const bool collision =
        (test_block_r1 & test_board_r1) | (test_block_r2 & test_board_r2) |
        (test_block_r3 & test_board_r3) | (test_block_r4 & test_board_r4);
    
    if (collision) {
        board_r1 |= block_r1;
        board_r2 |= block_r2;
        board_r3 |= block_r3;
        board_r4 |= block_r4;
    }
    else {
        state->x = x;
        state->y = y;
        state->rot = rot;
        test_board_r1 |= test_block_r1;
        test_board_r2 |= test_block_r2;
        test_board_r3 |= test_block_r3;
        test_board_r4 |= test_block_r4;
    }

    return !collision;
}

void toString(State* state, char* buf, size_t size) {
    struct StringLayout {
        char board[22][25];
        // "Next: [Z, L, O, S, I, J, T, Z, L, O, S, I, J, T]"
        char next[49];
        // "Hold: [Z]"
        char hold[10];
        // "Line: [    % 8d]"
        char line[17];
    };
    static const char board[22][25] = {
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','\n'},
        {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','\n'},
    };
    static const char next[] = {
        'N','e','x','t',':',' ','[',
        '?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',',',' ',
        '?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',',',' ','?',']','\n'
    };
    static const char hold[] = {'H','o','l','d',':',' ','[','Z',']','\n'};
    thread_local static State st;
    if (size < sizeof(StringLayout)) return;
    // Get shadow of current block
    memcpy(st.board, state->board, sizeof(st.board));
    st.current = state->current;
    st.rot = state->rot;
    st.x = state->x;
    st.y = state->y;
    while (softDrop(&st));
    // Print state to buf
    StringLayout* sl = reinterpret_cast<StringLayout*>(buf);
    memcpy(sl->board, board, sizeof(sl->board));
    memcpy(sl->next, next, sizeof(sl->next));
    memcpy(sl->hold, hold, sizeof(sl->hold));
    for (int i = 0; i < 21; i++) {
        uint32_t row = state->board[i + BOARD_TOP];
        uint32_t shd_row = st.board[i + BOARD_TOP];
        for (uint32_t mask = 0b00000000000000000000000011000000u, j = 21;
                      mask < 0b00000100000000000000000000100000u; mask <<= 2, j -= 2) {
            switch ((shd_row & mask) >> (27 - j)) {
            case 0b10:
            case 0b11:
                sl->board[i][j] = ':';
                sl->board[i][j - 1] = ':';
            }
            switch ((row & mask) >> (27 - j)) {
            case 0b01:
                sl->board[i][j] = sl->board[i][j - 1] = '#';
                break;
            case 0b10:
            case 0b11:
                sl->board[i][j] = ']';
                sl->board[i][j - 1] = '[';
                break;
            }
        }
    }
    for (int i = 0; i < 14; i++) {
        sl->next[7 + i * 3] = state->next[i]["?ZLOSIJT" + 1];
    }
    sl->hold[7] = state->hold[" ZLOSIJT" + 1];
    sprintf(sl->line, "Line: [% 8d]", state->clean_count);
    buf[sizeof(StringLayout) - 1] = '\0';
}

void eraseCurrent(State* state) {
    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];
    board_r1 ^= board_r1 & (ref_block_data[0] >> x_offset);
    board_r2 ^= board_r2 & (ref_block_data[1] >> x_offset);
    board_r3 ^= board_r3 & (ref_block_data[2] >> x_offset);
    board_r4 ^= board_r4 & (ref_block_data[3] >> x_offset);
}
void pasteCurrent(State* state) {
    auto& ref_block_data = blocks[state->current][state->rot].data;
    const int x_offset = state->x << 1;
    const int y_offset = BOARD_TOP + state->y;
    uint32_t& board_r1 = state->board[y_offset + 0];
    uint32_t& board_r2 = state->board[y_offset + 1];
    uint32_t& board_r3 = state->board[y_offset + 2];
    uint32_t& board_r4 = state->board[y_offset + 3];
    board_r1 |= ref_block_data[0] >> x_offset;
    board_r2 |= ref_block_data[1] >> x_offset;
    board_r3 |= ref_block_data[2] >> x_offset;
    board_r4 |= ref_block_data[3] >> x_offset;
}

void initialize() {
    // sseed(uint32_t(time(0)));
    next_block_permutations_initializer();
}

const Block(*block_data())[7][4] {
    return &blocks;
}
void* function_table() {
    static void* func_table[] = {
        reinterpret_cast<void*>(reset),
        reinterpret_cast<void*>(generateBlock),
        reinterpret_cast<void*>(moveLeft),
        reinterpret_cast<void*>(moveRight),
        reinterpret_cast<void*>(softDrop),
        reinterpret_cast<void*>(hardDrop),
        reinterpret_cast<void*>(rotateLeft),
        reinterpret_cast<void*>(rotateRight),
        reinterpret_cast<void*>(hold),
        reinterpret_cast<void*>(moveBlock),
        reinterpret_cast<void*>(toString),
        reinterpret_cast<void*>(eraseCurrent),
        reinterpret_cast<void*>(pasteCurrent),
        reinterpret_cast<void*>(block_data),
    };
    return func_table;
}
