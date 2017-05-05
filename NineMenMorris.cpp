#include "NineMenMorris.h"

using namespace AIProject;

NineMenMorris::NineMenMorris(){}


void NineMenMorris::display(){
	if(screen_ == Global::MENU_SCREEN){
		// If we are in the menu screen:
		menu_->display();
	} else if(screen_ == Global::GAME_SCREEN){
		// If we are playing:
		if(game_ != nullptr){
			game_->display();
		}
	}
}

void NineMenMorris::mouse(int button, int state, int x, int y){
	if(game_ != nullptr){
		game_->mouse(button, state, x, y);
	}
}

void NineMenMorris::keyboard(unsigned char key, int x, int y){
	key = toupper(key);

	if(screen_ == Global::MENU_SCREEN){
		// If we are in the menu screen:
		game_ = menu_->chooseGameMode(key);
		screen_ = Global::GAME_SCREEN;
		glutPostRedisplay();
	} else if(screen_ == Global::GAME_SCREEN){
		// If we are playing:
		switch(key){
			case 'R':
				// Restart the game
				game_ = menu_->lastGameMode();
				break;
			case 'M':
				// Go back to main menu
				screen_ = Global::MENU_SCREEN;
				game_ = nullptr;
				break;
		}
	}
}
