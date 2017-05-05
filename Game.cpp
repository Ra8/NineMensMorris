#include "Game.h"

using namespace AIProject;

Game::Game(int whitePlayer=0, int blackPlayer=1):
	board_(make_shared<Board>(Global::BOARD_WIDTH, Global::BOARD_HEIGHT)),
    gameState_(make_shared<State>()),
    AI_(make_shared<Agent>()),
    whitePlayer_(whitePlayer),
    blackPlayer_(blackPlayer)
    {
        reset();
        mainLoop();
}

void Game::display(){
    if(!updateScene_){
        return;
    }
    updateScene_ = false;
	glLoadIdentity();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(Global::SCREEN_SHRINK_RATIO/Global::SCREEN_WIDTH,
        -Global::SCREEN_SHRINK_RATIO/Global::SCREEN_HEIGHT,
        1);

	glTranslatef(-Global::SCREEN_WIDTH/2, -Global::SCREEN_HEIGHT/2, 0.0 );

    // Compute the extra colors needed to draw the board
    // 1 -> selected
    // 2 -> previously selected
    // 3 -> deleted
    array<int, 24> extraColors;
    extraColors.fill(0);
    if(selected_ >=0){
        extraColors[selected_] = 1;
    }
    if(previousSelected_ >=0){
        extraColors[previousSelected_] = 2;
    }
    if(deleted_ >=0){
        extraColors[deleted_] = 3;
    }
    board_->draw(gameState_, extraColors);

    // glutSwapBuffers();
    if(winner_ != Global::EMPTY){
        glColor4f(1,1,1,0.3);
        glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(Global::BOARD_WIDTH, 0);
            glVertex2f(Global::BOARD_WIDTH, Global::BOARD_HEIGHT);
            glVertex2f(0, Global::BOARD_HEIGHT);
        glEnd();

        string winnerText = "";
        if(winner_ == Global::WHITE){
            winnerText = "White";
        } else {
            winnerText = "Black";
        }
        winnerText += " Won!";

        TextRenderer::printCenter(Global::BOARD_WIDTH/2, 250, winnerText, 3);
    }

    glFlush();
}

void Game::mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        pos_ = board_->get(x,y);
        humanMove_.unlock();
    }
}

void Game::reset(){
    gameState_->reset();
    resetSelected();
}
void Game::makeMove(int color, int type){
    if(!playing_){
        return;
    }
    while(this->gameState_->getTurn() == color && playing_){
        if(type==0){
            // If the player is human
            // Lock until the human selects a cell
            humanMove_.lock();
            this->playTurn(this->pos_);
        } else {
            // If the player is an AI
            playTurn(this->AI_->getNextMove(*this->gameState_, type));
        }
    }
    if(color != this->gameState_->getTurn()){
        // If the turn changed
        // Check if we have a winner
        if(gameState_->isTerminal()){
            winner_ = color;
            return;
        }
        if(color == Global::WHITE){
            blackMove_.unlock();
        } else if(color == Global::BLACK) {
            whiteMove_.unlock();
        }
    }
}

void Game::mainLoop(){
    // Lock everything!
    whiteMove_.lock();
    blackMove_.lock();
    humanMove_.lock();
    for(int i=0;i<safeToDelete_.size();i++){
        safeToDelete_[i].lock();
    }

    // Function for a certain player
    auto colorFunction = [this](mutex& colorMove, int colorPlayer, int threadNum) -> void{
        while(playing_){
            // Lock player until it's their move
            colorMove.lock();
            makeMove(gameState_->getTurn(), colorPlayer);
            if(playing_){
                // If we're still playing update the screen
                updateScene_ = true;
                glutPostRedisplay();
            }
        }
        safeToDelete_[threadNum].unlock();
    };

    // Create a thread for each of the 2 players
    thread blackThread(colorFunction, ref(blackMove_), blackPlayer_, 0);
    thread whiteThread(colorFunction, ref(whiteMove_), whitePlayer_, 1);
    whiteThread.detach();
    blackThread.detach();

    // Let the game begin!
    whiteMove_.unlock();
}
void Game::resetSelected(){
    selected_ = -1;
    previousSelected_ = -1;
    deleted_ = -1;
}

void Game::nextTurn(int pos){
    // Check if there is a new mill formed and go to the next turn
    if(gameState_->checkMill(pos)){
        gameState_->setRemoveOpponent(true);
    } else {
        gameState_->incTurn();
    }
}

void Game::transferSelected(int pos){
    previousSelected_ = selected_;
    selected_ = pos;
    deleted_ = -1;
}

void Game::playTurn(int pos){
    if(!playing_){
        return;
    }
    if(pos==-2){
        resetSelected();
        gameState_->incTurn();
    } else if(pos == -1){
        resetSelected();
    } else {
        if(gameState_->getRemoveOpponent()){
            // If the current play is to remove one of the opponents
            auto removable = gameState_->getRemovable();
            if(find(removable.begin(), removable.end(), pos) != removable.end()){
                gameState_->setBoard(pos,Global::EMPTY);
                gameState_->setRemoveOpponent(false);
                gameState_->incTurn();
                deleted_ = pos;
            }
        } else if(gameState_->isPlacingPhase() && gameState_->getBoardAt(pos) == Global::EMPTY) {
            // If the current play is to place a piece
            gameState_->setBoard(pos, gameState_->getTurn());
            nextTurn(pos);
            gameState_->incPiecesPlaced();
            transferSelected(pos);
            previousSelected_ = -1;
        } else if(gameState_->isMovingPhase()
            && selected_ != -1
            && gameState_->getBoardAt(pos) == Global::EMPTY
            && gameState_->getBoardAt(selected_) == gameState_->getTurn()) {
            // If the current play is to move a piece
                if(gameState_->count(gameState_->getTurn())
                    || gameState_->areAdjacent(pos, selected_)) {
                        gameState_->setBoard(pos, gameState_->getTurn());
                        gameState_->setBoard(selected_, Global::EMPTY);
                        nextTurn(pos);
                }
                transferSelected(pos);
        } else {
            transferSelected(pos);
            previousSelected_ = -1;
        }
        updateScene_ = true;
    }
}

Game::~Game(){
    // safely unlock all locks to delete object
    playing_ = false;

    humanMove_.unlock();
    whiteMove_.unlock();
    blackMove_.unlock();

    for(int i=0;i<safeToDelete_.size();i++){
        safeToDelete_[i].lock();
        safeToDelete_[i].unlock();
    }
}