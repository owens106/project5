/*
	Project Assignment2
*/

#include "glut.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Point {
public:
	GLfloat xcord;
	GLfloat ycord;
	GLfloat zcord;
};

static int window; //variable that hold main window
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1.0;
double xcord = 0;
double ycord = 0;

double xpoint = 0;
double ypoint = 0;

float m[16];

BOOLEAN addPoint = false;
BOOLEAN lmbd = false;

vector<Point> vec;


void init() {
	// Set initial OpenGL states
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shiniess[] = { 20.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void drawCubeLocation(GLfloat xcenter, GLfloat ycenter, GLfloat size, GLfloat zpos) {

	glBegin(GL_POLYGON); //front face

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right

	glEnd();

	glBegin(GL_POLYGON);//back face
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glEnd();

	

	glBegin(GL_POLYGON); //left face
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glEnd();

	glBegin(GL_POLYGON);//right face
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glEnd();

	glBegin(GL_POLYGON);//top face
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glEnd();

	glBegin(GL_POLYGON);//bottom face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glEnd();

	glFlush();
}


void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0,1.0, -10.0, 10.0);

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
	glColor3f(1.0, 1.0, 0.0);

	glutWireSphere(radius, 20, 20);
	// Flush buffers to screen
	if (addPoint) {
		//derive from x^2 + y^2 + z^2 = r^2
		double zval = sqrt(abs(pow(xpoint, 2) + pow(ypoint, 2) - pow(radius, 2)));
		printf("in add point\n");
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		float xval = (xpoint * m[0] + ypoint * m[1] + zval * m[2]);
		float yval = xpoint * m[4] + ypoint * m[5] + zval * m[6];
		float zvalFinal = xpoint * m[8] + ypoint * m[9] + zval * m[10];
		Point point;
		point.xcord = xval;
		point.ycord = yval;
		point.zcord = zvalFinal;
		vec.push_back(point);
		addPoint = false;
	}

	for (int i = 0; i < vec.size(); i++) {
		glBegin(GL_POLYGON);
		double tempxcord = vec.at(i).xcord;
		double tempycord = vec.at(i).ycord;
		double tempzcord = vec.at(i).zcord;

		printf("\ntempxCord: %f", tempxcord);

		drawCubeLocation(tempxcord, tempycord, 0.02, tempzcord);


	}

		//draw lines between each vector, will eventually become curve loop
		glBegin(GL_LINES);
		for (int i = 0; i < vec.size(); i++) {
			double tempxcord = vec.at(i).xcord;
			double tempycord = vec.at(i).ycord;
			double tempzcord = vec.at(i).zcord;
			//glVertex3f(tempxcord, tempycord, tempzcord);
			/*if (vec.size() == 2) { //need to generate points between the two end points so that their z coord can be mapped to the surface of sphere.
				GLfloat tempFirstx = vec.at(1).xcord;
				GLfloat tempFirsty = vec.at(1).ycord;
				GLfloat tempFirstz = vec.at(1).zcord;

				GLfloat tempsecondx = vec.at(2).xcord;
				GLfloat tempsecondy = vec.at(2).ycord;
				GLfloat tempsecondz = vec.at(2).zcord;

				float min = tempFirstx;
				if (tempsecondx < tempFirstx) {
					min = tempsecondx;
				}



				float xdiff = abs(tempFirstx - tempsecondx);
				float yiff = abs(tempFirsty - tempsecondy);


			}*/
		}
		glEnd();
	

	//draw all points in vector
	


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
		lmbd = true;

	}

	if (button == 0 && mode == 1) {//release lmb
		lmbd = false;
	}

	if (button == 2 && mode == 0) {
		addPoint = true;

		//TODO always = 0,0 due to int divison. figure out why real values are off.
		//xpoint = x/(glutGet(GLUT_WINDOW_WIDTH));
		//ypoint = y / (glutGet(GLUT_WINDOW_HEIGHT));

		xpoint = 2.0f * ((GLfloat)x + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
		 ypoint = -1 * (2.0f * ((GLfloat)y + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f);


		printf("xpoint: %f, ypoint: %finsdie mouseclick\n",xpoint, ypoint);

		glutPostRedisplay();
	}


	//printf("Xrotated:   %f,  Yrotated   %f", xRotated, yRotated);
	return;
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down
	//printf("mouse down at pos: %d , %d\n", x, y);
	if (lmbd) {
		GLfloat xdiff = xcord - (GLfloat)x;
		GLfloat ydiff = ycord - (GLfloat)y;
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
	glutInitWindowSize(480, 480);
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