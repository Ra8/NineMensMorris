#ifndef AIPROJECT_NINEMENMORRIS_H
#define AIPROJECT_NINEMENMORRIS_H

#include <GL/glut.h>
#include <iostream>
#include <memory>
#include "Game.h"
#include "Menu.h"
using namespace std;

namespace AIProject{
	/**
	 * @class NineMenMorris
	 * This class organizes the different scenes that show up
	 */
	class NineMenMorris {
	public:
		/** 
		 * NineMenMorris Constructor
		 */
		NineMenMorris();
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
		
		void keyboard(unsigned char key, int x, int y);
	private:
		/// An instance of the game
		shared_ptr<Game> game_ = nullptr;
		/// An instance of the menu
		shared_ptr<Menu> menu_ = make_shared<Menu>();
		/// Current Screen showing
		int screen_ = Global::MENU_SCREEN;
	};
}

#endif