#ifndef AIPROJECT_STATE_H
#define AIPROJECT_STATE_H

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
#include "Global.h"
using namespace std;

namespace AIProject{
	/**
	 * @class Game
	 * This class organizes Glut's mouse and display events
	 * This also manages when each player should play.
	 */
	class State {
	public:
		/** 
		 * State Constructor
		 */
		State();
		/** 
		 * Resets all the values for a new game
		 */
		void reset();
		/** 
		 * Get the current turn
		 * @return the value of the current player's turn
		 */
		int getTurn();
		/** 
		 * Get the next player's turn
		 * @return the value of the next player's turn
		 */
		int getNextTurn();
		/** 
		 * @return true if we are in the placing phase
		 */
		bool isPlacingPhase();
		/** 
		 * @return true of we are in the moving phase
		 */
		bool isMovingPhase();
		/** 
		 * @return true if the current player just formed a mill and has to remove one of the oppoent's pieces
		 */
		bool getRemoveOpponent();
		/** 
		 * @return the number of pieces placed
		 */
		int getPiecesPlaced();
		/** 
		 * @param pos the position on the board
		 * @return the value of the piece at the board's position pos
		 */
		int getBoardAt(int pos);
		/** 
		 * @returns the whole board state
		 */
		array<int, 24> getBoardState();
		/** 
		 * @param player the player value
		 * @return the number of pieces the player has on the board
		 */
		int count(int player);
		/** 
		 * @param pos the position on the board
		 * @return true if the move to position pos forms a new mill 
		 */
		bool checkMill(int pos);
		/** 
		 * This function returns all the positions that the opponent can delete
		 * If all the opponent positions form mills then any piece can be removed
		 * otherwise only the pieces that are not part of mills can be removed
		 * @return all the positions that the oponent can remove
		 */
		vector<int> getRemovable();
		/** 
		 * @param pos1 position 1 on the board
		 * @param pos2 position 2 on the board
		 * @return true if pos1 and pos2 are adjacent on the board
		 */
		bool areAdjacent(int pos1, int pos2);

		/** 
		 * Increases the pieces placed and updated the phase when
		 * it reaches 18
		 */
		void incPiecesPlaced();
		/** 
		 * Sets the position pos to the player player
		 * @param pos the position on the board
		 * @param player the value of the player
		 */
		void setBoard(int pos, int player);
		/** 
		 * Sets the phase to Moving Phase
		 */
		void incPhase();
		/** 
		 * Sets wether the current player can remove one of the opponent's player
		 * after forming a mill to flag
		 * @param flag
		 */
		void setRemoveOpponent(bool flag);
		/** 
		 * Sets the turn to the opponent
		 */
		void incTurn();

		/** 
		 * Joins all the data needed to form a singlr 64 bit integer
		 * that encodes the whole state of the game
		 * @return this integer
		 */
		long long serialize();
		/** 
		 * This does the reverse of serialize. Reconstructs the game state
		 * from the 64 bit integer state that is passed
		 * @param state the encoding of the state
		 */
		void deserialize(long long state);
		/** 
		 * Tries all possible rotation and flips and returns a unique state
		 * that represents all of the 8 possible orderings
		 * @return the 64 bit integer that encodes all these 8 states
		 */
		long long getUniqueState();

		/** 
		 * Compute all the possible next state fromt the current state.
		 * This is needed by the AI to explore the possibilities
		 * @return a set of all the possible next states
		 */
		set<long long> getAllNextState();
		/** 
		 * Returns all the possible next states from the current state
		 * in the moving phase by moving the pos piece
		 * @param pos the position on the board
		 * @return a set of all the possible next states
		 */
		set<long long> getNextStatesFromPosMoving(int pos);
		/** 
		 * Returns all the possible next states from the current state
		 * in the placing phase by placing a piece at position pos
		 * @param pos the position on the board
		 * @return a set of all the possible next states
		 */
		set<long long> getNextStatesFromPosPlacing(int pos);

		/** 
		 * Returns the moves needed to go from the current state to
		 * the state passed
		 * @param state the new state that we are trying to figure out the moves to get to
		 * @return the set of moves needed to do
		 */
		vector<int> getMove(long long state);
		/** 
		 * Returns the moves needed to go from the current state to
		 * the state passed in the moving phase when moving the pos piece
		 * @param pos the position on the board
		 * @param state the new state that we are trying to figure out the moves to get to
		 * @return the set of moves needed to do
		 */
		vector<int> getMoveFromPosMoving(int pos, long long state);
		/** 
		 * Returns the moves needed to go from the current state to
		 * the state passed in the placing phase when placing the pos piece
		 * @param pos the position on the board
		 * @param state the new state that we are trying to figure out the moves to get to
		 * @return the set of moves needed to do
		 */
		vector<int> getMoveFromPosPlacing(int pos, long long state);

		/** 
		 * @return true iff the current player has lost
		 */
		bool isTerminal();
		/** 
		 * Compute an evaluation of the state passed
		 * @param state the 64 bit integer that reperesents the state
		 * @return the value of the state
		 */
		int stateValue1(long long state);

	private:
		/// The board state, each index indiciates wehter it's occupied by a white or black piece or if it's empty 
		array<int, 24> boardState_;
		/// The number of white pieces on board
		int p1_ = 0;
		/// The number of black pieces on board
		int p2_ = 0;
		/// Stores the turn of the current player
		int turn_;
		/// Stores the current phase
		int phase_;
		/// True if the current player can remove one of the opponent's player
		bool removeOpponent_;
		/// The number of pieces placed
		int piecesPlaced_;
		/// Stores the adjacent cells
		static const vector<set<int>> adjacent_;
		/// Stores the mills positions that can be formed
		static const vector<array<int, 3>> lines_;
		/// Stores the mills positions that can be formed for each index
		static array<vector<array<int, 3>>, 24> compactLines_;
		/// Stores all the rotations and flips that can be done
		static vector<array<int, 24>> swaps_;
		/// Stores all the possible positions, needed for the "Flying" phase
		static const set<int> allPos_;
	};
}

#endif