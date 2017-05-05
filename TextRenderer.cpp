#include "TextRenderer.h"

using namespace AIProject;

void TextRenderer::print(int x, int y, string text, double size){
	glPushMatrix();
		glLoadIdentity();
		glScalef(Global::SCREEN_SHRINK_RATIO/Global::SCREEN_WIDTH,
	        -Global::SCREEN_SHRINK_RATIO/Global::SCREEN_HEIGHT,
	        1);

		glTranslatef(x-Global::SCREEN_WIDTH/2, y-Global::SCREEN_HEIGHT/2, 0.0);
		glScalef(0.2*size, -0.2*size, 0.0);
		glLineWidth(size*1.5);
		glColor3f(0,0,0);
		for(auto ch: text){
	    	glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
		}
	glPopMatrix();
}
void TextRenderer::printCenter(int x, int y, string text, double size){
	double width = textWidth(text, size);
	print(x-width/2, y, text, size);
}

double TextRenderer::textWidth(string text, double size){
	glPushMatrix();
		glLoadIdentity();
		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
		
		GLfloat matrix[16]; 
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix); 
		double before = matrix[12];
		glScalef(0.2*size, -0.2*size, 0.0);
		for(auto ch: text){
	    	glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
		}
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix); 
		double width = (matrix[12]-before)/matrix[0]*0.2*size;
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glPopMatrix();
	return width;
}
