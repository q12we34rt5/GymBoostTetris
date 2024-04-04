#include "TetrisHQ.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define __SPEEDUP__

Block::Block(Type type, int width, int height, BlockDatas data)
	: type(type), width(width), height(height), data{} {
    memcpy(this->data, &data, sizeof(this->data));
	//for (int k = 0; k < 4; k++) {
	//	this->data[k] = new uint8_t * [height];
	//	for (int i = 0; i < height; i++) {
	//		this->data[k][i] = new uint8_t[width];
	//		for (int j = 0; j < width; j++)
	//			this->data[k][i][j] = (*reinterpret_cast<uint8_t(*)[4][4][4]>(&data))[k][i][j];
	//	}
	//}
}

const Block blocks[Block::Type::LENGTH] = {
	{
		Block::Type::Z,
		3, 3,
		{
			{
				{0x32, 0x3C, 0x00},
				{0x00, 0x33, 0x38},
				{0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x00, 0x34},
				{0x00, 0x36, 0x39},
				{0x00, 0x31, 0x00}
			},
			{
				{0x00, 0x00, 0x00},
				{0x32, 0x3C, 0x00},
				{0x00, 0x33, 0x38}
			},
			{
				{0x00, 0x34, 0x00},
				{0x36, 0x39, 0x00},
				{0x31, 0x00, 0x00}
			}
		}
	},
	{
		Block::Type::L,
		3, 3,
		{
			{
				{0x00, 0x00, 0x44},
				{0x42, 0x4A, 0x49},
				{0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x44, 0x00},
				{0x00, 0x45, 0x00},
				{0x00, 0x43, 0x48}
			},
			{
				{0x00, 0x00, 0x00},
				{0x46, 0x4A, 0x48},
				{0x41, 0x00, 0x00}
			},
			{
				{0x42, 0x4C, 0x00},
				{0x00, 0x45, 0x00},
				{0x00, 0x41, 0x00}
			}
		}
	},
	{
		Block::Type::O,
		4, 3,
		{
			{
				{0x00, 0x56, 0x5C, 0x00},
				{0x00, 0x53, 0x59, 0x00},
				{0x00, 0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x56, 0x5C, 0x00},
				{0x00, 0x53, 0x59, 0x00},
				{0x00, 0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x56, 0x5C, 0x00},
				{0x00, 0x53, 0x59, 0x00},
				{0x00, 0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x56, 0x5C, 0x00},
				{0x00, 0x53, 0x59, 0x00},
				{0x00, 0x00, 0x00, 0x00}
			}
		}
	},
	{
		Block::Type::S,
		3, 3,
		{
			{
				{0x00, 0x66, 0x68},
				{0x62, 0x69, 0x00},
				{0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x64, 0x00},
				{0x00, 0x63, 0x6C},
				{0x00, 0x00, 0x61}
			},
			{
				{0x00, 0x00, 0x00},
				{0x00, 0x66, 0x68},
				{0x62, 0x69, 0x00}
			},
			{
				{0x64, 0x00, 0x00},
				{0x63, 0x6C, 0x00},
				{0x00, 0x61, 0x00}
			}
		}
	},
	{
		Block::Type::I,
		4, 4,
		{
			{
				{0x00, 0x00, 0x00, 0x00},
				{0x72, 0x7A, 0x7A, 0x78},
				{0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x00, 0x74, 0x00},
				{0x00, 0x00, 0x75, 0x00},
				{0x00, 0x00, 0x75, 0x00},
				{0x00, 0x00, 0x71, 0x00}
			},
			{
				{0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00},
				{0x72, 0x7A, 0x7A, 0x78},
				{0x00, 0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x74, 0x00, 0x00},
				{0x00, 0x75, 0x00, 0x00},
				{0x00, 0x75, 0x00, 0x00},
				{0x00, 0x71, 0x00, 0x00}
			}
		}
	},
	{
		Block::Type::J,
		3, 3,
		{
			{
				{0x84, 0x00, 0x00},
				{0x83, 0x8A, 0x88},
				{0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x86, 0x88},
				{0x00, 0x85, 0x00},
				{0x00, 0x81, 0x00}
			},
			{
				{0x00, 0x00, 0x00},
				{0x82, 0x8A, 0x8C},
				{0x00, 0x00, 0x81}
			},
			{
				{0x00, 0x84, 0x00},
				{0x00, 0x85, 0x00},
				{0x82, 0x89, 0x00}
			}
		}
	},
	{
		Block::Type::T,
		3, 3,
		{
			{
				{0x00, 0x94, 0x00},
				{0x92, 0x9B, 0x98},
				{0x00, 0x00, 0x00}
			},
			{
				{0x00, 0x94, 0x00},
				{0x00, 0x97, 0x98},
				{0x00, 0x91, 0x00}
			},
			{
				{0x00, 0x00, 0x00},
				{0x92, 0x9E, 0x98},
				{0x00, 0x91, 0x00}
			},
			{
				{0x00, 0x94, 0x00},
				{0x92, 0x9D, 0x00},
				{0x00, 0x91, 0x00}
			}
		}
	}
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
static constexpr int BOARD_LEFT   = 4;
static constexpr int BOARD_RIGHT  = BOARD_LEFT + 9;

static uint32_t seed = 123456789;

void sseed(uint32_t seed) {
    ::seed = seed;
}

static uint32_t xorshf32() {
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
    while (std::next_permutation(next, next + 7)) {
        //memcpy(&next_block_permutations[index++], next, sizeof(next));
        compact_memory& ref = next_block_permutations[index++];
        ref.b0 = unsigned(next[0]);
        ref.b1 = unsigned(next[1]);
        ref.b2 = unsigned(next[2]);
        ref.b3 = unsigned(next[3]);
        ref.b4 = unsigned(next[4]);
        ref.b5 = unsigned(next[5]);
        ref.b6 = unsigned(next[6]);
    }

    end = clock();
    return end - start;
}
//static const clock_t next_block_permutations_initialize_cost_time = next_block_permutations_initializer();

static inline void randomBlocks(Block::Type dest[]) {
    //memcpy(dest, next_block_permutations[xorshf32() % 5040], sizeof(int8_t) * 7);
    compact_memory& ref = next_block_permutations[xorshf32() % 5040];
    dest[0] = Block::Type(ref.b0);
    dest[1] = Block::Type(ref.b1);
    dest[2] = Block::Type(ref.b2);
    dest[3] = Block::Type(ref.b3);
    dest[4] = Block::Type(ref.b4);
    dest[5] = Block::Type(ref.b5);
    dest[6] = Block::Type(ref.b6);
}

#else

static inline void randomBlocks(Block::Type dest[]) {
    static const Block::Type init[] = { Block::Z, Block::L, Block::O, Block::S, Block::I, Block::J, Block::T };
    memcpy(dest, init, sizeof(int8_t) * 7);
    for (int i = 0; i < 7; i++) {
        uint32_t rnd = xorshf32() % 7;
        Block::Type temp = dest[i];
        dest[i] = dest[rnd];
        dest[rnd] = temp;
    }
    for (int i = 0; i < 7; i++) {
        uint32_t rnd = xorshf32() % 7;
        Block::Type temp = dest[i];
        dest[i] = dest[rnd];
        dest[rnd] = temp;
    }
}

#endif

inline static void clean(State* state) {
    memset(state->board, 0x1f, sizeof(state->board));
    for (int i = 0; i <= BOARD_BOTTOM; i++)
		for (int j = BOARD_LEFT; j <= BOARD_RIGHT; j++)
			state->board[i][j] = 0x00;
	//for (int i = 0; i < BOARD_HEIGHT; i++) {
	//	state->board[i][BOARD_LEFT - 1] = state->board[i][BOARD_RIGHT + 1] = 0x15;
	//}
	//for (int j = 0; j < width; j++) {
	//	_data[sy - 1][j + sx] = 0x00;
	//	_data[height + sy][j + sx] = 0x1A;
	//}
	//_data[sy][sx - 1] = 0x14;
	//_data[sy - 1][sx - 1] = 0x14;
	//_data[height + sy][sx - 1] = 0x13;
	//_data[sy][width + sx] = 0x14;
	//_data[sy - 1][width + sx] = 0x14;
	//_data[height + sy][width + sx] = 0x19;
}

inline bool fullFilled(State* state, int index) {
    bool full = true;
    for (int i = BOARD_LEFT; i <= BOARD_RIGHT; i++)
        full &= bool(state->board[index][i]);
    return full;
}

inline int cleanLines(State* state) {
    int count = 0;
    for (int i = BOARD_BOTTOM; i >= BOARD_TOP; i--) {
        while (fullFilled(state, i - count)) {
            memset(state->board[i - count] + BOARD_LEFT, 0x00, 10);
            for (int j = BOARD_LEFT; j <= BOARD_RIGHT; j++) {
                state->board[i - count - 1][j] &= 0xFB;
                state->board[i - count + 1][j] &= 0xFE;
            }
            count++;
        }
        memcpy(state->board[i] + BOARD_LEFT, state->board[i - count] + BOARD_LEFT, 10);
    }
    return count;
}

inline void pasteBlock(State* state, int x, int y, Block::Type type, uint8_t rot) {
	auto& b = blocks[type];
	for (int i = 0; i < b.height; i++)
		for (int j = 0; j < b.width; j++) {
			const int cx = BOARD_LEFT + x + j, cy = BOARD_TOP + y + i;
			state->board[cy][cx] |= b.data[rot][i][j];
		}
}
inline void eraseBlock(State* state, int x, int y, Block::Type type, uint8_t rot) {
	auto& b = blocks[type];
	for (int i = 0; i < b.height; i++)
		for (int j = 0; j < b.width; j++) {
			const int cx = BOARD_LEFT + x + j, cy = BOARD_TOP + y + i;
			state->board[cy][cx] -= b.data[rot][i][j];
		}
}
inline int testCollision(State* state, int x, int y, Block::Type type, uint8_t rot) {
	auto& b = blocks[type];
	int collisionTimes = 0;
	for (int i = 0; i < b.height; i++)
		for (int j = 0; j < b.width; j++) {
			const int cx = BOARD_LEFT + x + j, cy = BOARD_TOP + y + i;
			collisionTimes += !!(state->board[cy][cx] && b.data[rot][i][j]);
		}
	return collisionTimes;
}

void reset(State* state) {
    clean(state);
    state->game_state = true;
    randomBlocks(state->next);
    randomBlocks(state->next + 7);
    state->hold = Block::NONE;
    state->has_holded = false;
    state->current = Block::NONE;
    state->rot = 0;
    state->x = -1;
    state->y = -1;
    state->clean_count = 0;
}

bool generateBlock(State* state) {
    int line_count = cleanLines(state);
    state->clean_count += line_count;

    state->has_holded = false;

    Block::Type cur = state->next[0];
    state->x = 3;
    state->y = 0;
    state->rot = 0;

    const int collision = testCollision(state, state->x, state->y, cur, state->rot);

    if (collision) {
        state->game_state = false;
        return false;
    }

    state->current = cur;

    pasteBlock(state, state->x, state->y, cur, state->rot);

    // shift the next blocks
    for (int i = 0; i < 13; i++)
        state->next[i] = state->next[i + 1];
    state->next[13] = Block::NONE;

    // generate new random blocks if needed
    if (state->next[7] == Block::NONE) {
        randomBlocks(state->next + 7);
    }

    return true;
}

bool moveLeft(State* state) {
    const int test_x = state->x - 1;
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    const int collision = testCollision(state, test_x, state->y, state->current, state->rot);
    if (!collision)
        state->x = test_x;
    pasteBlock(state, state->x, state->y, state->current, state->rot);
    return !collision;
}
bool moveRight(State* state) {
    const int test_x = state->x + 1;
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    const int collision = testCollision(state, test_x, state->y, state->current, state->rot);
    if (!collision)
        state->x = test_x;
    pasteBlock(state, state->x, state->y, state->current, state->rot);
    return !collision;
}
bool softDrop(State* state) {
    const int test_y = state->y + 1;
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    const int collision = testCollision(state, state->x, test_y, state->current, state->rot);
    if (!collision)
        state->y = test_y;
    pasteBlock(state, state->x, state->y, state->current, state->rot);
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
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    for (int i = 0; i < rot_tests_len; i++) {
        const int srs_x_offset = srs_rot_tests[i].x;
        const int srs_y_offset = srs_rot_tests[i].y;
        const int test_x_offset = state->x + srs_x_offset;
        const int test_y_offset = state->y - srs_y_offset;
        const int collision = testCollision(state, test_x_offset, test_y_offset, state->current, test_rot);
        if (!collision) {
            state->rot = test_rot;
            state->x += srs_x_offset;
            state->y -= srs_y_offset;
            pasteBlock(state, state->x, state->y, state->current, state->rot);
            return true;
        }
    }
    pasteBlock(state, state->x, state->y, state->current, state->rot);
    return false;
}
bool rotateRight(State* state) {
    const int8_t test_rot = (state->rot + 1) % 4;
    // get wall kick tests
    auto& srs_rot_tests = srs[state->current].test[state->rot][1];
    auto& rot_tests_len = srs[state->current].length;
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    for (int i = 0; i < rot_tests_len; i++) {
        const int srs_x_offset = srs_rot_tests[i].x;
        const int srs_y_offset = srs_rot_tests[i].y;
        const int test_x_offset = state->x + srs_x_offset;
        const int test_y_offset = state->y - srs_y_offset;
        const int collision = testCollision(state, test_x_offset, test_y_offset, state->current, test_rot);
        if (!collision) {
            state->rot = test_rot;
            state->x += srs_x_offset;
            state->y -= srs_y_offset;
            pasteBlock(state, state->x, state->y, state->current, state->rot);
            return true;
        }
    }
    pasteBlock(state, state->x, state->y, state->current, state->rot);
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
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    generateBlock(state);
    state->has_holded = true;
    return true;
}

bool moveBlock(State* state, int x, int y, int8_t rot) {
    eraseBlock(state, state->x, state->y, state->current, state->rot);
    const int collision = testCollision(state, x, y, state->current, state->rot);
    if (!collision) {
        state->x = x;
        state->y = y;
        state->rot = rot;
    }
    pasteBlock(state, state->x, state->y, state->current, state->rot);
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
        for (int j = 1; j <= 10; j++) {
            uint8_t shadow_data = st.board[BOARD_TOP + i][BOARD_LEFT + j - 1];
            uint8_t block_data  = state->board[BOARD_TOP + i][BOARD_LEFT + j - 1];
            if (shadow_data) sl->board[i][j << 1] = sl->board[i][(j << 1) + 1] = (shadow_data >> 4)[" X$zlosijt"];
            if (block_data) sl->board[i][j << 1] = sl->board[i][(j << 1) + 1] = (block_data >> 4)[" X$ZLOSIJT"];
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
    eraseBlock(state, state->x, state->y, state->current, state->rot);
}
void pasteCurrent(State* state) {
    pasteBlock(state, state->x, state->y, state->current, state->rot);
}

void initialize() {
    sseed(uint32_t(time(0)));
    next_block_permutations_initializer();
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
    };
    return func_table;
}
