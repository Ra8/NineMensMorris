#include <GL/glut.h>
#include <memory>
#include "Global.h"
#include "NineMenMorris.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
const bool isWindows = true;
#else
const bool isWindows = false;
#endif


using namespace AIProject;

// Create an instance of the game
auto nineMen(make_shared<NineMenMorris>());


void display() {
	nineMen->display();
}
void display2(int x) {
	glutPostRedisplay();
	glutTimerFunc(100, display2, 0);
}
void mouse(int button, int state, int x, int y) {
	nineMen->mouse(button, state, x, y);
}
void keyboard(unsigned char key, int x, int y){
	nineMen->keyboard(key, x, y);
}
 
int main(int argc, char** argv) {
	if(isWindows){
		FreeConsole();
	}

	// Initialize GLUT
	glutInit(&argc, argv);
	// Create a window with the given title
	glutCreateWindow("Nine Men Morris");
	// Set the window's initial width & height
	glutInitWindowSize(Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT);
	glutReshapeWindow(Global::SCREEN_WIDTH, Global::SCREEN_HEIGHT);
	// Register display callback handler for window re-paint 
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100,display2,2);
	// Enter the event-processing loop
	glutMainLoop();
	return 0;
}