#ifndef AIPROJECT_BOARD_H
#define AIPROJECT_BOARD_H

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include "State.h"
#include "Global.h"
#include "TextRenderer.h"
using namespace std;

namespace AIProject{
	/**
	 * @class Board
	 * This class handles the painting of the board
	 */
	class Board {
	public:
		/** 
		 * Board Constructor
		 */
		Board();
		/** 
		 * Board Constructor
		 * @param width the width of the board
		 * @param height the height of the board
		 */
		Board(int width, int height);
		/** 
		 * Draws the board according the the state passed and the extra
		 * colors needed to tell the user which piece was last moved,
		 * and which piece was last removed
		 * @param gameState the current state of the game
		 * @param extraColors the extra rings needed to give the user more information
		 */
		void draw(shared_ptr<State> gameState, array<int, 24>& extraColors);
		/** 
		 * Given the x and y coordinate of the mouse, returns the color of the piece
		 * that the mouse is over, or -1 if there is no piece below it
		 * @param x the x coordinate of the mouse
		 * @param y the y coordinate of the mouse
		 * @return the color of the piece pointed at
		 */
		int get(int x, int y);
	private:
		/**
		 * Function that handles the drawing of a circle using the line loop
		 * method. This will create a hollow or filled circle.
		 * @param x the x coordinate of the center point of the circle
		 * @param y the y position of the center point of the circle
		 * @param radius the radius tof the circle
		 * @param filled wether the circle is filled or not
		 */
		void drawCircle(GLfloat x, GLfloat y, GLfloat radius, bool filled);
		/** 
		 * Calls the openGL function to create a vertex at the point passed
		 * @param p the point that we need the vertex created at
		 */
		void makePoint(pair<int,int> p);
		/** 
		 * Computes the sqaured euclidian distance between
		 * (x1,y1) and (x2,y2)
		 * @param x1 the first x coordinate
		 * @param y1 the first y coordinate
		 * @param x2 the second x coordinate
		 * @param y2 the second y coordinate
		 * @return the distance
		 */
		int sqDistance(int x1, int y1, int x2, int y2);
		/** 
		 * Draws the grid of the board
		 */
		void drawBoard();
		/** 
		 * Calls the openGL methods to change the color to color
		 * @param color the RGB color encoded in a single integer
		 */
		void changeColor(int color);

		/// Percentage of the content of the board
		double content_ = 0.9;
		/// The radius of an empty cell
		int smallRadius_=6;
		/// The radius of a cell with a piece
		int radius_=12;
		/// The x offset of the outer board to the inner board
		int widthOffset_;
		/// The y offset of the outer board to the inner board
		int heightOffset_;
		/// The corners of the board
		vector<pair<int,int> > corners_ = {
			{0,0},{3,0},{6,0},
			{1,1},{3,1},{5,1},
			{2,2},{3,2},{4,2},
			{0,3},{1,3},{2,3},{4,3},{5,3},{6,3},
			{2,4},{3,4},{4,4},
			{1,5},{3,5},{5,5},
			{0,6},{3,6},{6,6}
			};
		/// The width of the board
		int width_;
		/// The outer width of the board
		int outerWidth_;
		/// The height of the board
		int height_;
		/// The outer height of the board
		int outerHeight_;
	};
}

#endif
