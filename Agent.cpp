#include "Agent.h"

using namespace AIProject;

Agent::Agent(){
	rng_.seed(time(0));
}
int Agent::getNextMove(State s, int algo){
	if(nextMoves_.size()!=0){
		// If we already have something stored
		// Return the first value and erase it
		int nextMove = nextMoves_[0];
		nextMoves_.erase(nextMoves_.begin());
		return nextMove;
	} else {
		// Compute the best move using minimax
		long long org = s.serialize();
		turn_= s.getTurn();
		long long nextState = -1;
		nextState = minimax(org);

		s.deserialize(org);
		nextMoves_ = s.getMove(nextState);
		if(nextMoves_.size()==0){
			throw domain_error("Number of moves should be at least 1");
		}
		return getNextMove(s, algo);
	}
}

long long Agent::minimax(long long cState){
	stateValues_.clear();
	auto result = minimax(cState, 0, -100, 100);
	return result.first;
}
pair<long long, int> Agent::minimax(long long cState, int depth, int alpha, int beta){
	if(stateValues_.find(cState) != stateValues_.end()){
		return stateValues_[cState];
	} else
	if(depth==maxDepth_){
		int multiplier = (turn_%2)*(-2)+1;
		long long value = tmpState_.stateValue1(cState)*multiplier;
		return {cState, value};
	}  else {
		tmpState_.deserialize(cState);
		auto possibleStates = tmpState_.getAllNextState();
		// Convert the set to a vector in order to shuffle
		vector<long long> possibleStatesVector(possibleStates.begin(),possibleStates.end());
		if(possibleStatesVector.size()==0){
			int val = 20;
			if(turn_==Global::WHITE){
				val*=-1;
			}
			return stateValues_[cState] = {cState, val};
		}
		// shuffle the first level only
		if(depth==0){
			auto rng = [this](int i){
				uniform_int_distribution<int> dist(0,i-1);
				return dist(this->rng_);
			};
			random_shuffle(possibleStatesVector.begin(), possibleStatesVector.end(), rng);
		}
		long long bestState = -1;
		int bestValue = 0;
		// loop over all possible next states
		for(auto nextPossibleState: possibleStatesVector){
			auto bestNextState = minimax(nextPossibleState, depth+1, alpha, beta);
			int bestNextValue = bestNextState.second;
			if(depth == 0){
			}
			// Choose the max or the min based on who's turn it is
			if((bestNextValue > bestValue || bestState == -1) && depth%2==0){
				bestValue = bestNextValue;
				bestState = nextPossibleState;
				alpha = max(alpha, bestValue);
				if(beta <= alpha){
					break; 
				}
			} else if((bestNextValue < bestValue || bestState == -1) && depth%2==1){
				bestValue = bestNextValue;
				bestState = nextPossibleState;
				beta = min(beta, bestValue);
				if(beta <= alpha){
					break; 
				}
			}
		}
		return stateValues_[cState] = {bestState, bestValue};
	}
}