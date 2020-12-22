/*
	Project Assignment2
*/

#include "glut.h"
#include <iostream>
#include <stdio.h>
#include <vector>



static int window; //variable that hold main window
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;
double xcord = 0;
double ycord = 0;




void init() {
	// Set initial OpenGL states
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shiniess[] = { 20.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}


void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.5, 1.5, -1.5 * (GLfloat)480 / (GLfloat)640,
		1.5 * (GLfloat)480 / (GLfloat)640, -10.0, 10.0);

	//gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.1, 21.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}


// display function
void display() {

	//glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the identity matrix.
	glLoadIdentity();
	// traslate the draw by z = -4.0
	// Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	glTranslatef(0.0, 0.0, -4.0);
	// Red color used to draw.
	//glColor3f(0.9, 0.3, 0.2);
	// changing in transformation matrix.
	// rotation about X axis
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a sphere.
	glutSolidSphere(radius, 200, 200);
	// Flush buffers to screen

	glFlush();
	// sawp buffers called because we are using double buffering 
   // glutSwapBuffers();

}
/*
Function invoked when an event on a regular keys occur.
*/
void keyboard(unsigned char k, int x, int y)
{
	// Close application if ESC is pressed 
	if (k == 27)
	{
		exit(0);
	}
}




/*
Mouse Handler
*/
void mouseClick(int button, int mode, int x, int y) {
	// event happens once on pushing the button and once more when releasing it
	// button identifies what you clicked, mode if its down or up
	printf("%d, %d , %d, %d\n", button, mode, x, y);
	printf("mouseclicked\n");
	if (button == 0 && mode == 0) {
		//left mouse down
		xcord = x;
		ycord = y;
	}

	//printf("Xrotated:   %f,  Yrotated   %f", xRotated, yRotated);
	return;
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down
	//printf("mouse down at pos: %d , %d\n", x, y);
	GLfloat xdiff = xcord - x;
	GLfloat ydiff = ycord - y;
	xcord = x;
	ycord = y;
	printf("inside mouse motion with x: %d, y: %d\nxdiff: %f, ydiff: %f\n", x, y, xdiff, ydiff);
	if (xdiff >= 0 && ydiff >= 0) {
		yRotated += xdiff;
		xRotated -= ydiff;
	}
	else if (xdiff >= 0 && ydiff <= 0) {
		yRotated += xdiff;
		xRotated -= ydiff;
	}
	else if (xdiff <= 0 && ydiff >= 0) {
		yRotated += xdiff;
		xRotated -= ydiff;
	}
	else if (xdiff <= 0 && ydiff <= 0) {
		yRotated += xdiff;
		xRotated += ydiff;
	}
	display();
	return;
}
void resize(int width, int height) {
	//this is called on window resize
	//params are window width and window height
}




/*
The main function.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Solid Sphere");
	zRotated = 30.0;
	xRotated = 0;
	yRotated = 0;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	init();
	glutMainLoop();
	return 0;
}