#ifdef __APPLE__
#include <GLUT/glut.h>  //Include for MAC
#endif
#ifndef __APPLE__
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>

using namespace std;

vector<int> draw_sequence; //Stores the sequence in which, triangles will be drawn.
bool notDrawn[] = {true,true,true,true}; //Stores whether the triangle is already drawn or not.

// ofset, colour
//{x,y,z, r,g,b,a}
float triangles[][7] = {
	{-0.5f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f, 0.65f}, //Triangle 1 colour red  alpha=0.65
	{ 0.0f, 0.0f, 0.1f, 1.0f, 1.0f, 0.0f, 1.0f},	//Triangle 2 colour yellow  alpha=1 (opaque)
	{ 0.5f, 0.0f, 0.3f, 0.0f, 1.0f, 1.0f, 0.5f},	//Triangle 3 colour light blue  alpha=0.5
	{ 0.0f,-0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.25f},	//Triangle 4 colour green  alpha=0.25
};

// x,y,z : offset from center triangle
// r,g,b : colour value
// a : opacity (Alpha value in [0,1] where 0 represents fully transparent and 1 represents opaque)
void drawTriangle(float x,float y, float z, float r,float g,float b,float a){
		glBegin(GL_TRIANGLES);
		glColor4f(r,g,b,a);
		glVertex3f( 0.0f+x,  0.5f+y, 0.0f+z);
		glVertex3f( 0.5f+x, -0.5f+y, 0.0f+z);
		glVertex3f(-0.5f+x, -0.5f+y, 0.0f+z);
		glEnd();
}


void renderFunction(void) {
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int i=0;i<draw_sequence.size();i++){
	 	int curr=draw_sequence[i];
		drawTriangle(triangles[curr][0],triangles[curr][1],triangles[curr][2],triangles[curr][3],triangles[curr][4],triangles[curr][5],triangles[curr][6]);
	}

	// Swap front and back buffers
	glutSwapBuffers();
}


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
			if(notDrawn[0]){
				draw_sequence.push_back(0);
				notDrawn[0]=false;
			}
      break;
    case '2':
			if(notDrawn[1]){
				draw_sequence.push_back(1);
				notDrawn[1]=false;
			}
      break;
    case '3':
			if(notDrawn[2]){
				draw_sequence.push_back(2);
				notDrawn[2]=false;
			}
      break;
    case '4':
			if(notDrawn[3]){
				draw_sequence.push_back(3);
				notDrawn[3]=false;
			}
      break;

    case 'r':
			draw_sequence.clear();
			for(int i=0;i<4;i++) {
				 notDrawn[i]=true;
			}
      break;
		case 'o':
		  glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
			glMatrixMode(GL_MODELVIEW);
			break;
		case 'p':
		  glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		  gluPerspective(80.0, 1.0, 1.0, 20.0);
			glMatrixMode(GL_MODELVIEW);
			break;
		case 27:
			exit(0);
  }
	//Redraw
	glutPostRedisplay();
}



void init()
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
	// View setup
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 2.0,  // eye is at (0,0,2)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Alpha Compositing");

	init();

  //Sets the default background colour [ used by glClear(GL_COLOR_BUFFER_BIT) ]
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//Enable Alpha Compositing
	glEnable(GL_BLEND);

	//Set the method to be used for Alpha Compositing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Refer : https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml

	// register callbacks
	glutDisplayFunc(renderFunction);
  glutKeyboardFunc(processNormalKeys);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
