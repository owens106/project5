/*
	Project Assignment2
*/

#include "glut.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
# define PI		3.14159265358979323846

class Point {
public:
	GLfloat xcord;
	GLfloat ycord;
	GLfloat zcord;
	float rcolor = 1.0;
	float bcolor = 0.0;
	float gcolor = 0.0;
};

static int window; //variable that hold main window
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1.0;
double xcord = 0;
double ycord = 0;

float xpoint = 0;
float ypoint = 0;

float m[16];
float y[16];

BOOLEAN addPoint = false;
BOOLEAN lmbd = false;

float globalAngle = 0;
Point globalP0;
Point globalP1;

float timevar;

vector<Point> vec;



void select(int index) {
	for (int i = 0; i < vec.size(); i++) {
		if (i == index) {
			vec.at(i).gcolor = 1.0;
			vec.at(i).rcolor = 0.0;
		}
		else {
			vec.at(i).rcolor = 1.0;
			vec.at(i).gcolor = 0.0;
		}
	}
}

void slerp(vector<Point> vec) {
	if (vec.size() == 1) {
		return;
	}

	float t = 0.266;

	vector<Point> tempVec;
	for (int i = 0; i < vec.size()-1; i++) {
		//printf("size:%d", vec.size());
		Point p0 = vec.at(i);
		Point p1 = vec.at(i + 1);

		float len0 = sqrt((pow(p0.xcord, 2)) + (pow(p0.ycord, 2)) + (pow(p0.zcord, 2))); //magnitube
		float len1 = sqrt((pow(p1.xcord, 2)) + (pow(p1.ycord, 2)) + (pow(p1.zcord, 2)));
		globalP0 = p0;
		globalP1 = p1;
		
		p0.xcord = p0.xcord / len0; //normalize
		p0.ycord = p0.ycord / len0;
		p0.zcord = p0.zcord / len0;

		p1.xcord = p1.xcord / len1;
		p1.ycord = p1.ycord / len1;
		p1.zcord = p1.zcord / len1;



		float dot = (p0.xcord * p1.xcord) + (p0.ycord * p1.ycord) + (p0.zcord * p1.zcord); //dot product
		
		float angle = acos(dot / (1 * 1)); //angle between two vectors
		
		//printf("angle:%f\n", angle);

		Point nextPoint;
		float alpha = (sin(1 - t) * angle) / sin(angle);
		float beta = sin(t * angle) / sin(angle);
		nextPoint.xcord = alpha * p0.xcord + beta * p1.xcord;
		nextPoint.ycord = alpha * p0.ycord + beta * p1.ycord;
		nextPoint.zcord = alpha * p0.zcord + beta * p0.zcord;
		tempVec.push_back(nextPoint);
		globalAngle = angle;


		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 1.0);
		for (float i = 0; i <= 1; i += 0.01f) { //draw line between points
			float alpha = sin((1 - i) * angle) / sin(angle);
			float beta = sin(i * angle) / sin(angle);

			float fixedP0xcord, fixedP0ycord, fixedP0zcord, fixedP1xcord, fixedP1ycord, fixedP1zcord;
			glGetFloatv(GL_MODELVIEW_MATRIX, m);

			//printf("testing: %f : %f : %f\n", y[0], y[1],y[2]);


			/*fixedP0xcord = globalP0.xcord * m[0] + globalP0.ycord * m[1] + globalP0.zcord * y[2];
			fixedP0ycord = globalP0.xcord * m[4] + globalP0.ycord * m[5] + globalP0.zcord * m[6];
			fixedP0zcord = globalP0.xcord * m[8] + globalP0.ycord * m[9] + globalP0.zcord * m[10];

			fixedP1xcord = globalP1.xcord * m[0] + globalP1.ycord * m[1] + globalP1.zcord * m[2];
			fixedP1ycord = globalP1.xcord * m[4] + globalP1.ycord * m[5] + globalP1.zcord * m[6];
			fixedP1zcord = globalP1.xcord * m[8] + globalP1.ycord * m[9] + globalP1.zcord * m[10];

			float xcordDraw = alpha * fixedP0xcord + beta * fixedP1xcord;
			float ycordDraw = alpha * fixedP0ycord + beta * fixedP1ycord;
			float zcordDraw = alpha * fixedP0zcord + beta * fixedP1zcord;
			*/

			//printf("xcord: %f, ycord: %f, z cord:%f\n", xcordDraw, ycordDraw, zcordDraw);
			

			float xcord = alpha * p0.xcord + beta * p1.xcord;
			float ycord = alpha * p0.ycord + beta * p1.ycord;
			float zcord = alpha * p0.zcord + beta * p1.zcord;
			//printf("xcord: %f, ycord: %f, z cord: %f\n", xcord, ycord, zcord);
			

			/*glGetFloatv(GL_MODELVIEW_MATRIX, m);

			 xcord = (xcord * m[0] + ycord * m[1] + zcord * m[2]);
			 ycord = xcord * m[4] + ycord * m[5] + zcord * m[6];
			 zcord = xcord * m[8] + ycord * m[9] + zcord * m[10];
			// printf("xcord: %f, ycord: %f, z cord: %f\n", xcord, ycord, zcord);
			 printf("testing123: %f: %f: %f\n", m[0], m[1], m[2]);
			 printf("testing123: %f: %f: %f\n", y[0], y[1], y[2]);
			 */

			//glVertex3f(xcordDraw, ycordDraw, zcordDraw);

			glVertex3f(xcord, ycord, zcord);
		}
		glEnd();
		
	}

	slerp(tempVec);
}


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

void drawCubeLocation(GLfloat xcenter, GLfloat ycenter, GLfloat size, GLfloat zpos, float rcolor, float gcolor, float bcolor) {

	glBegin(GL_POLYGON); //front face

	glColor3f(rcolor, bcolor, gcolor);

	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left

	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left

	glVertex3f(xcenter + size, ycenter - size, zpos - size); //bottom right

	glVertex3f(xcenter + size, ycenter + size, zpos - size); //top right

	glEnd();

	glBegin(GL_POLYGON);//back face
	glVertex3f(xcenter + size, ycenter + size, zpos + size); //top right
	glVertex3f(xcenter + size, ycenter - size, zpos + size); //bottom right
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glEnd();

	

	glBegin(GL_POLYGON); //left face
	glVertex3f(xcenter - size, ycenter - size, zpos - size); //bottom left
	glVertex3f(xcenter - size, ycenter + size, zpos - size); //top left
	glVertex3f(xcenter - size, ycenter + size, zpos + size); //top left
	glVertex3f(xcenter - size, ycenter - size, zpos + size); //bottom left
	glEnd();

	glBegin(GL_POLYGON);//right face
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
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		float xval = (xpoint * m[0] + ypoint * m[1] + zval * m[2]); //fix points to align with rotation
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


		drawCubeLocation(tempxcord, tempycord, 0.02, tempzcord, vec.at(i).rcolor, vec.at(i).bcolor, vec.at(i).gcolor);


	}
	
	if (vec.size() > 1) {			
		slerp(vec);
			
	}
	

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
	int z = glutGetModifiers();

	if (button == 0 && mode == 0 && z == 0) {
		//left mouse down no modifiers
		xcord = x;
		ycord = y;
		lmbd = true;

	}

	if (button == 0 && mode == 1) {//release lmb
		lmbd = false;
	}

	if (button == 2 && mode == 0) { //rmb down
		addPoint = true;

		xpoint = 2.0f * ((GLfloat)x + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
		 ypoint = -1 * (2.0f * ((GLfloat)y + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f);

		glutPostRedisplay();
	}


	if (z == 1 && button == 0 && mode == 0) { //shift Lclick down
		//select point
		lmbd = true;
		float localx = 2.0f * ((GLfloat)x + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_WIDTH)) - 1.0f; //convert to same scale as points
		float localy = -1 * (2.0f * ((GLfloat)y + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f);
		float templocalx = localx;


		double zval = sqrt(abs(pow(localx, 2) + pow(localy, 2) - pow(radius, 2)));
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		localx = (localx * m[0] + localy * m[1] + zval * m[2]); //fix points to align with rotation/align with x,y, coords as points on sphere

		localy = templocalx * m[4] + localy * m[5] + zval * m[6];

		//float zvalFinal = xpoint * m[8] + ypoint * m[9] + zval * m[10];




		for (int i = 0; i < vec.size(); i++) {
			if ((abs(vec.at(i).xcord - localx) < 0.05) && (abs(vec.at(i).ycord - localy) < 0.05)) { //find first point that is within the tolerance. change its color
				select(i);
				break;
			}
		}
	}

	//printf("Xrotated:   %f,  Yrotated   %f", xRotated, yRotated);
	return;
}
void mouseMotion(int x, int y) {
	// called when the mouse moves
	// active motion means a button is down
	//printf("mouse down at pos: %d , %d\n", x, y);
	int z = glutGetModifiers();

	if (lmbd && z == 0) {
		GLfloat xdiff = xcord - (GLfloat)x;
		GLfloat ydiff = ycord - (GLfloat)y;
		xcord = x;
		ycord = y;
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
	} //end if

	if (z == 1 && lmbd) { //shift being held with left mouse
		//start shifting the selected point;
		printf("inside shift movement\n");
		int index = -1;
		for (int i = 0; i < vec.size(); i++) {
			if (vec.at(i).gcolor == 1.0) { //selected point
				index = i;
			}
		}//end for
		if (index == -1) { //no point found
			printf("no selected point!\n");
			return;
		}
		float localx = 2.0f * ((GLfloat)x + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_WIDTH)) - 1.0f; //convert to same scale as points
		float localy = -1 * (2.0f * ((GLfloat)y + 0.5f) / (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT)) - 1.0f);
		float templocalx = localx;


		double zval = sqrt(abs(pow(localx, 2) + pow(localy, 2) - pow(radius, 2)));
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		localx = (localx * m[0] + localy * m[1] + zval * m[2]); //fix points to align with rotation/align with x,y, coords as points on sphere

		localy = templocalx * m[4] + localy * m[5] + zval * m[6];

		vec.at(index).xcord = localx;
		vec.at(index).ycord = localy;
		

	}
	glutPostRedisplay();


}//end mouse move
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