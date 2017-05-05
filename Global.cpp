#include "Global.h"
using namespace AIProject;

const int Global::SCREEN_WIDTH = 700;
const int Global::SCREEN_HEIGHT = 500;
const double Global::SCREEN_SHRINK_RATIO = 2;

const int Global::BOARD_WIDTH = 500;
const int Global::BOARD_HEIGHT = 500;
const int Global::BOARD_BG = 0xF7E4D2;

const int Global::EMPTY_COLOR = 0x9B9B9B;
const int Global::WHITE_COLOR = 0xFFFFFF;
const int Global::BLACK_COLOR = 0x000000;
const array<int,4> Global::RING_COLOR = {0x141414,0xFF0000,0x00FF00,0x0000FF};
const int Global::GRID_COLOR = 0x9B9B9B;

const bool Global::CIRCLE_FILL = true;
const bool Global::CIRCLE_HOLLOW = false;

const int Global::PLACING_PHASE = 0;
const int Global::MOVING_PHASE = 1;

const int Global::EMPTY = 0;
const int Global::WHITE = 1;
const int Global::BLACK = 2;

const int Global::MENU_SCREEN = 0;
const int Global::GAME_SCREEN = 1;
const int Global::SKIP_SCREEN = 2;
