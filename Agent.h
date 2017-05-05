#ifndef AIPROJECT_AGENT_H
#define AIPROJECT_AGENT_H
#include <set>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <map>
#include <random>
#include <ctime>
#include "State.h"
using namespace std;

namespace AIProject{
	/**
	 * @class Agent
	 * This class manages the AI of the game using the minimax algorithm
	 */
	class Agent {
	public:
		Agent();
		/** 
		 * Computes the next move
		 * @param s the state that we need to compute the move from
		 * @param algo the algorithm to use when computing the next state [not used]
		 * @return the position of the piece that we want to perform our move to
		 */
		int getNextMove(State s, int algo);
	private:
		/** 
		 * The initial call to minimax from the current state
		 * @param cState the current state we are at
		 * @return the state we should move to
		 */
		long long minimax(long long cState);
		/** 
		 * The minimax algorithm with alpha beta pruning
		 * @param cState the current state
		 * @param depth how deep are we in the minimax algorithm
		 * @param alpha the alpha value
		 * @param beta the beta value
		 * @return the best state to be at, and its value
		 */
		pair<long long, int> minimax(long long cState, int depth, int alpha, int beta);

		/// Memoized values when computing the minimax of the current state
		map<long long, pair<long long, int>> stateValues_;
		/// A dummy state object that is used to serialize and deserialze and compute the next possible states
		State tmpState_;
		/// Stores the next moves without recomputing anything
		vector<int> nextMoves_;
		/// The maximum depth of the minimax search
		int maxDepth_ = 6;
		/// Random number generator
		mt19937 rng_;
		/// The color of the player getting the next move
		int turn_;
	};
}

#endif