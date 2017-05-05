#include "Menu.h"

using namespace AIProject;


Menu::Menu(){

}

void Menu::display(){
	glLoadIdentity();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	// Print the menu:
	TextRenderer::printCenter(Global::SCREEN_WIDTH/2, 100, "Nine Men's Morris", 2);
	TextRenderer::printCenter(Global::SCREEN_WIDTH/2, 130, "A project by Rene Adaimi", 0.9);
	TextRenderer::print(100, 240, "Use the keyboard to select one of following options:", 0.6);
	TextRenderer::print(100, 280, "W: Play white against computer", 1.2);
	TextRenderer::print(100, 330, "B: Play black against computer", 1.2);
	TextRenderer::print(100, 380, "H: Play against another human", 1.2);
	TextRenderer::print(100, 430, "X: Let AI play against each other", 1.2);

	glFlush();
}

shared_ptr<Game> Menu::lastGameMode(){
	return chooseGameMode(lastChoice_);
}

shared_ptr<Game> Menu::chooseGameMode(char key){
	lastChoice_ = key;
	// Select appropriate game mode:
	switch(key){
		case 'W':
			return make_shared<Game>(0,defaultAIBlack_);
		case 'B':
			return make_shared<Game>(defaultAIWhite_,0);
		case 'H':
			return make_shared<Game>(0,0);
		case 'X':
			return make_shared<Game>(defaultAIWhite_, defaultAIBlack_);
		default:
			return nullptr;
	}
}
