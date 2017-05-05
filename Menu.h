#ifndef AIPROJECT_MENU_H
#define AIPROJECT_MENU_H

#include <GL/glut.h>
#include <iostream>
#include <memory>
#include "Game.h"
using namespace std;

namespace AIProject{
	/**
	 * @class Menu
	 * This class organizes the different scenes that show up
	 */
	class Menu {
	public:
		/** 
		 * Menu Constructor
		 */
		Menu();
		/**
		 * This function manages Glut's display function
		 */
		void display();
		/**
		 * From the main menu, selects a game mode from:
		 * 		- Play against another human
		 * 		- Play white against AI
		 * 		- Play black against AI
		 * 		- Let AI play against each other
		 * @param key The key pressed to select player
		 * @return an instance of a game in the mode selected
		 */
		shared_ptr<Game> chooseGameMode(char key);
		/**
		 * From the playing board, restarts the game with the same option selected previously
		 * @return an instance of a game in the mode selected previously
		 */
		shared_ptr<Game> lastGameMode();
	private:
		/// Default algorithm for the white AI [not used]
		int defaultAIWhite_ = 2;
		/// Default algorithm for the black AI [not used]
		int defaultAIBlack_ = 2;
		/// Last pressed key for a game choice
		char lastChoice_ = '\0';
	};
}

#endif