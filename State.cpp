#include "State.h"

using namespace AIProject;

const vector<set<int>> State::adjacent_ = {
	{1,9}, 		// 0
	{0,2,4}, 	// 1
	{1,14}, 	// 2
	{10,4}, 	// 3
	{1,3,5,7}, 	// 4
	{4,13}, 	// 5
	{7,11}, 	// 6
	{4,6,8}, 	// 7
	{7,12}, 	// 8
	{0,10,21}, 	// 9
	{3,9,11,18},// 10
	{6,10,15},	// 11
	{8,13,17},	// 12
	{5,12,14,20},//13
	{2,13,23},	// 14
	{11,16},	// 15
	{15,17,19},	// 16
	{12,16},	// 17
	{10,19},	// 18
	{16,18,20,22},//19
	{13,19},	// 20
	{9,22},		// 21
	{19,21,23},	// 22
	{14,22}		// 23
};
const vector<array<int,3>> State::lines_ = {
	{0,1,2},
	{3,4,5},
	{6,7,8},
	{9,10,11},
	{12,13,14},
	{15,16,17},
	{18,19,20},
	{21,22,23},
	{0,9,21},
	{3,10,18},
	{6,11,15},
	{1,4,7},
	{16,19,22},
	{8,12,17},
	{5,13,20},
	{2,14,23}
};

array<vector<array<int, 3>>, 24> State::compactLines_;

vector<array<int, 24>> State::swaps_;

const set<int> State::allPos_ = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};

State::State(){
	reset();
	vector<vector<vector<int>>> allBoards = {{
		{0 , -1, -1, 1 , -1, -1, 2 },
		{-1, 3 , -1, 4 , -1, 5 , -1},
		{-1, -1, 6 , 7 , 8 , -1, -1},
		{9 , 10, 11, -1, 12, 13, 14},
		{-1, -1, 15, 16, 17, -1, -1},
		{-1, 18, -1, 19, -1, 20, -1},
		{21, -1, -1, 22, -1, -1, 23}}
	};
	// compute all possible rotations of the board
	for(int k=0;k<3;k++){
		auto newBoard = allBoards[0];
		for(int i=0;i<newBoard.size();i++){
			for(int j=0;j<newBoard[i].size();j++){
				newBoard[i][j]=allBoards.back()[j][newBoard.size()-1-i];
			}
		}
		allBoards.push_back(newBoard);
	}
	// compute all possible flips of the board
	int originalSize = allBoards.size(); 
	for(int k=0;k<originalSize;k++){
		auto newBoard=allBoards[k];
		for(int i=0;i<newBoard.size();i++){
			for(int j=0;j<newBoard.size()/2;j++){
				swap(newBoard[i][j],newBoard[i][newBoard[i].size()-1-j]);
			}
		}
		allBoards.push_back(newBoard);
	}
	// Compress the board into an array of size 24
	auto first = allBoards[0];
	for(int k=0;k<allBoards.size();k++){
		auto swapConfiguration = boardState_;
		for(int i=0;i<first.size();i++){
			for(int j=0;j<first[i].size();j++){
				swapConfiguration[first[i][j]]=allBoards[k][i][j];
			}
		}
		swaps_.push_back(swapConfiguration);
	}
	// Create compact lines:
	for(auto line: lines_){
		for(auto index: line){
			compactLines_[index].push_back(line);
		}
	}
}

int State::getTurn(){
	return turn_;
}

int State::getNextTurn(){
	return (turn_%2 + 1);
}

bool State::isPlacingPhase(){
	return phase_ == Global::PLACING_PHASE;
}

bool State::isMovingPhase(){
	return phase_ == Global::MOVING_PHASE;
}

bool State::getRemoveOpponent(){
	return removeOpponent_;
}

int State::getPiecesPlaced(){
	return piecesPlaced_;
}

int State::getBoardAt(int pos){
	return boardState_[pos];
}

array<int, 24> State::getBoardState(){
	return boardState_;
}

int State::count(int player){
	return ::count(boardState_.begin(), boardState_.end(), player);
}

bool State::checkMill(int pos){
	// Check if the move to position "pos" forms a mill
	auto& lines = compactLines_[pos];
	for(auto& line: lines){
		bool isWon = true;
		for(auto i: line){
            isWon = isWon&&(boardState_[i] == turn_);
		}
		if(isWon){
			return true;
		}
	}
	return false;
}

vector<int> State::getRemovable(){
	vector<int> removable;
	vector<int> unremovable;
	incTurn();
	for(int i=0;i<boardState_.size();i++){
		if(boardState_[i] == turn_){
			//Check if the current piece is part of any mill
			if(checkMill(i)){
				unremovable.push_back(i);
			} else {
				removable.push_back(i);
			}
		}
	}
	incTurn();
	// If all the pieces are part of a mill
	// we return all the pieces, otherwise
	// we return the pieces that are not part of any mill
	if(removable.size()>0){
		return removable;
	} else {
		return unremovable;
	}
}


bool State::areAdjacent(int pos1, int pos2){
	return adjacent_[pos1].find(pos2) != adjacent_[pos1].end();
}


void State::incPiecesPlaced(){
	piecesPlaced_++;
	if(piecesPlaced_ == 18){
		incPhase();
	}
}

void State::setBoard(int pos, int player){
	boardState_[pos] = player;
}

void State::incPhase(){
	phase_ = Global::MOVING_PHASE;
}

void State::setRemoveOpponent(bool flag){
	removeOpponent_ = flag;
}

void State::incTurn(){
	turn_ = getNextTurn();
}


void State::reset(){
    boardState_.fill(Global::EMPTY);
    turn_ = 1;
    phase_ = Global::PLACING_PHASE;
    removeOpponent_ = false;
    piecesPlaced_ = 0;
}


long long State::serialize(){
	// Construct a single 64bit integer from the current state
	long long state = 0;
	for(int i=0;i<boardState_.size();i++){
		state = state*3 + boardState_[i];
	}
	state = state*2 + (turn_-1);
	state = state*10 + (piecesPlaced_/2);
	return state;
}

void State::deserialize(long long state){
	// Reconstruct the full state from the 64bit integer
	piecesPlaced_ = (state%10)*2;
	state/=10;
	turn_ = state%2 +1;
	state/=2;
	p1_=0;
	p2_=0;
	for(int i=boardState_.size()-1;i>=0;i--){
		boardState_[i]=state%3;
		if(boardState_[i]==1){
			p1_++;
		} else if(boardState_[i]==2){
			p2_++;
		}
		state/=3;
	}
	removeOpponent_ = false;
	phase_ = Global::PLACING_PHASE;
	
	if(turn_ == 2){
		piecesPlaced_++;
	}
	if(piecesPlaced_ >= 18){
		phase_ = Global::MOVING_PHASE;
	}
}

long long State::getUniqueState(){
	// Loop over all possible rotations and flips
	// And return the smallest integer that can represent this state
	auto originalBoard = boardState_;
	long long mn=serialize();
	for(int i=swaps_.size()-1;i>=0;i--){
		for(int j=0;j<originalBoard.size();j++){
			boardState_[j]=originalBoard[swaps_[i][j]];
		}
		mn = min(mn, serialize());
	}
	return mn;
}

set<long long> State::getNextStatesFromPosMoving(int pos){
	// Returns all possible states from moving the "pos" piece
	set<long long> states;
	auto adjacent = adjacent_[pos];
	if(turn_==1 && p1_==3 || turn_==2 && p2_==3){
		adjacent = allPos_;
	}
	for(auto &i: adjacent){
		if(boardState_[i]==0){
			boardState_[i]=turn_;
			boardState_[pos]=0;
			if(checkMill(i)){
				auto removable = getRemovable();
				for(auto index: removable){
					boardState_[index]=0;
					incTurn();
					states.insert(getUniqueState());
					incTurn();
					boardState_[index]=getNextTurn();
				}
			} else {
				incTurn();
				states.insert(getUniqueState());
				incTurn();
			}
			boardState_[i]=0;
			boardState_[pos]=turn_;
		}
	}
	return states;
}

set<long long> State::getNextStatesFromPosPlacing(int pos){
	// Returns all possible states from placing the "pos" piece
	set<long long> states;
	boardState_[pos]=turn_;
	if(checkMill(pos)){
		auto removable = getRemovable();
		for(auto index: removable){
			boardState_[index]=0;
			incTurn();
			piecesPlaced_++;
			states.insert(getUniqueState());
			piecesPlaced_--;
			incTurn();
			boardState_[index]=getNextTurn();
		}
	} else {
		incTurn();
		piecesPlaced_++;
		states.insert(getUniqueState());
		piecesPlaced_--;
		incTurn();
	}
	boardState_[pos]=0;
	return states;
}	


set<long long> State::getAllNextState(){
	// Returns all possible states from the current state
	set<long long> allStates;
	for(int i=0;i<boardState_.size();i++){
		if(boardState_[i] == turn_ && phase_ == Global::MOVING_PHASE){
			auto newStates = getNextStatesFromPosMoving(i);
			allStates.insert(newStates.begin(), newStates.end());
		} else if(boardState_[i] == 0 && phase_ == Global::PLACING_PHASE){
			auto newStates = getNextStatesFromPosPlacing(i);
			allStates.insert(newStates.begin(), newStates.end());
		}
	}
	return allStates;
}

vector<int> State::getMoveFromPosMoving(int pos, long long state){
	// Returns the moves made by moving "pos" and that got into state
	vector<int> ans;
	auto adjacent = adjacent_[pos];
	if(turn_==1 && p1_==3 || turn_==2 && p2_==3){
		adjacent = allPos_;
	}
	for(auto &i: adjacent){
		if(boardState_[i]==0){
			boardState_[i]=turn_;
			boardState_[pos]=0;
			if(checkMill(i)){
				auto removable = getRemovable();
				for(auto index: removable){
					boardState_[index]=0;
					incTurn();
					long long cs = getUniqueState();
					incTurn();
					if(cs==state){
						ans.push_back(pos);
						ans.push_back(i);
						ans.push_back(index);
					}
					boardState_[index]=getNextTurn();
				}
			} else {
				incTurn();
				long long cs = getUniqueState();
				incTurn();
				if(cs==state){
					ans.push_back(pos);
					ans.push_back(i);
				}
			}
			boardState_[i]=0;
			boardState_[pos]=turn_;
		}
		if(ans.size()>0){
			break;
		}
	}
	return ans;
}
vector<int> State::getMoveFromPosPlacing(int pos, long long state){
	// Returns the moves made by placing "pos" and that got into state
	vector<int> ans;
	boardState_[pos]=turn_;
	if(checkMill(pos)){
		auto removable = getRemovable();
		for(auto index: removable){
			boardState_[index]=0;
			incTurn();
			piecesPlaced_++;
			long long cs = getUniqueState();
			piecesPlaced_--;
			incTurn();
			if(cs==state){
				ans.push_back(pos);
				ans.push_back(index);
			}
			boardState_[index]=getNextTurn();
		}
	} else {
		incTurn();
		piecesPlaced_++;
		long long cs = getUniqueState();
		piecesPlaced_--;
		incTurn();
		if(cs==state){
			ans.push_back(pos);
		}
	}
	boardState_[pos]=0;
	return ans;
}

vector<int> State::getMove(long long state){
	// Returns the move that got us into the "state" state
	vector<int> ans;
	for(int i=0;i<boardState_.size();i++){
		if(boardState_[i] == turn_ && phase_ == Global::MOVING_PHASE){
			ans = getMoveFromPosMoving(i,state);
		} else if(boardState_[i] == 0 && phase_ == Global::PLACING_PHASE){
			ans = getMoveFromPosPlacing(i,state);
		}
		if(ans.size() > 0){
			return ans;
		}
	}
	return ans;
}

bool State::isTerminal(){
	return (
		this->count(turn_) <= 2 && phase_ == Global::MOVING_PHASE
		|| getAllNextState().size()==0
		);
}

int State::stateValue1(long long state){
	deserialize(state);
	int score=p2_-p1_;

	// Check if we have a winner
	if(phase_ == Global::MOVING_PHASE){
		if(p1_<=2){
			score = 20;
		} else if(p2_<=2){
			score = -20;
		}
	}
	return score;
}
