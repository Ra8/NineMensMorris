#ifndef AIPROJECT_TEXT_RENDERER_H
#define AIPROJECT_TEXT_RENDERER_H

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "Global.h"
using namespace std;

namespace AIProject{
	/**
	 * @class TextRenderer
	 * This class organizes printing using Glut
	 */
	class TextRenderer {
	public:
		/**
		 * This function prints the text on the screen
		 * @param x The x coordinate of the text to be printed
		 * @param y The y coordinate of the text to be printed
		 * @param text The text to be printed
		 * @param size The size of the text to be printed
		 */
		static void print(int x, int y, string text, double size);
		/**
		 * This function prints the text in the middle of the x position
		 * @param x The x coordinate of the center of the text to be printed
		 * @param y The y coordinate of the text to be printed
		 * @param text The text to be printed
		 * @param size The size of the text to be printed
		 */
		static void printCenter(int x, int y, string text, double size);
		/**
		 * This function computes the length of the text that is going to be printed
		 * @param text The text to be printed
		 * @param size The size of the text to be printed
		 * @return the size of the text to be printed
		 */
		static double textWidth(string text, double size);
	};
}

#endif