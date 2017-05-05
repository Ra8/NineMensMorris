#ifndef AIPROJECT_GLOBAL_H
#define AIPROJECT_GLOBAL_H
#include <array>
using namespace std;

namespace AIProject{
	class Global {
	public:
		/// The screen width
		static const int SCREEN_WIDTH;
		/// The screen height
		static const int SCREEN_HEIGHT;
		/// The shrink ratio of the screen
		static const double SCREEN_SHRINK_RATIO;

		/// The board width
		static const int BOARD_WIDTH;
		/// The board height
		static const int BOARD_HEIGHT;
		/// The board's background color
		static const int BOARD_BG;
		
		/// The empty cell color
		static const int EMPTY_COLOR;
		/// The white color
		static const int WHITE_COLOR;
		/// The black color
		static const int BLACK_COLOR;
		/// The ring colors needed
		static const array<int,4> RING_COLOR;
		/// The grid's color
		static const int GRID_COLOR;
		
		/// Boolean value for the filled circle
		static const bool CIRCLE_FILL;
		/// Boolean value for the hollow circle
		static const bool CIRCLE_HOLLOW;

		/// Value of the placing phase
		static const int PLACING_PHASE;
		/// Value of the moving phase
		static const int MOVING_PHASE;

		/// Value of the empty cell
		static const int EMPTY;
		/// Value of the white player
		static const int WHITE;
		/// Value of the black player
		static const int BLACK;
		
		/// Value that means that the menu is showing
		static const int MENU_SCREEN;
		/// Value that means that the game is showing
		static const int GAME_SCREEN;
		/// Value that means that we don't want to draw anything
		static const int SKIP_SCREEN;

	};
}

#endif
