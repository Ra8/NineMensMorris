#ifndef AIPROJECT_GAME_H
#define AIPROJECT_GAME_H

#include <GL/glut.h>
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include "Board.h"
#include "Agent.h"
#include "State.h"
#include "Global.h"
#include <thread>
#include <mutex>
using namespace std;

namespace AIProject{
	/**
	 * @class Game
	 * This class organizes Glut's mouse and display events
	 * This also manages when each player should play.
	 */
	class Game {
	public:
		/** 
		 * Game Constructor
		 */
		Game(int whitePlayer, int blackPlayer);
		/**
		 * This function manages Glut's display function
		 */
		void display();
		/**
		 * This function manages Glut's mouse function
		 * @param button The button that was activated 
		 * @param state The state of the button that was activated 
		 * @param x The x coordinate of the position of the mouse
		 * @param y The y coordinate of the position of the mouse
		 */
		void mouse(int button, int state, int x, int y);
		/**
		 *	This function resets all the values needed to restart a game
		 */
		void reset();
		/**
		 * This function creates 2 threads and enables the player and the AI
		 * to play the game.
		 */
		void mainLoop();
		/**
		 * Game Destructor, safely unlocks all mutexes before deleting
		 */
		~Game();
	private:
		/**
		 * This function checks if the player is human or AI
		 * Then computes the move accordingly
		 * @param color The color of the current player moving
		 * @param type The type of the current player moving (Human or AI)
		 */
		void makeMove(int color, int type);
		/**
		 * This function checks if the position pos creates a mill
		 * if it does, the player can remove a piece from the opponent
		 * otherwise it's the opponent's turn
		 * @param pos The position of the piece that was played by the current player
		 */
		void nextTurn(int pos);
		/**
		 * This function plays the move selected_ -> pos in the game
		 * If we are in the placing phase, selected_ is ignored
		 * @param pos The position of the piece that was played by the current player
		 */
		void playTurn(int pos);
		/**
		 * This function resets the selected_, previousSelected_ and deleted_ variables
		 */
		void resetSelected();
		/**
		 * This function transfers selected_ to previousSelected_
		 * and pos to selected_
		 * @param pos The position of the piece that was played by the current player
		 */
		void transferSelected(int pos);

		/// This points to the class that draws the board based on the current state
		shared_ptr<Board> board_;
		/// This points to the class that encapsulates the state of the game
		shared_ptr<State> gameState_;
		/// This points to the class that manages the A.I. agent that playes against the human player
		shared_ptr<Agent> AI_;
		/// This mutex is unlocked everytime the human player makes a move
		mutex humanMove_;
		/// This mutex is unlocked everytime the white player makes a move
		mutex whiteMove_;
		/// This mutex is unlocked everytime the black player makes a move
		mutex blackMove_;
		/// Mutex to indicated that the object is safe to be deleted
		array<mutex,2> safeToDelete_;

		/// This is the last position that was played by the human player
		int pos_;
		/// This boolean is true whenever the scene needs to be updated
		bool updateScene_ = true;
		/// This boolean is true as long as the game is still on
		bool playing_ = true;

		/// This stores the currenlty selected piece on the board
		int selected_;
		/// This stores the previously selected piece on the board
		int previousSelected_;
		/// This stores the last piece that was removed from the board
		int deleted_;
		/// The type of the white player
		int whitePlayer_;
		/// The type of the black player
		int blackPlayer_;
		/// The winner of this game
		int winner_ = Global::EMPTY;
	};
}

#endif