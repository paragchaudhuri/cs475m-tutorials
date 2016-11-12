/*
* Reference: https://www.opengl.org/archives/resources/code/samples/glut_examples/examples/examples.html
*            http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard/
*            http://www.lighthouse3d.com/tutorials/glut-tutorial/animation/
*/
#ifdef __APPLE__
#include <GLUT/glut.h>  //Include for MAC
#endif
#ifndef __APPLE__
#include <GL/glut.h>
#endif

#include<iostream>

using namespace std;

float x_angle=0.0;
float y_angle=0.0;
float z_angle=0.0;
float offset=5.0;

//6 faces, 2 triangles/face, 3 vertices/triangle = 36 , each point in 3 dimension {x,y,z}
float v_positions[36][3] = {
  {-1.0,1.0,1.0},  {-1.0,-1.0,1.0},  {1.0,-1.0,1.0},
  {-1.0,1.0,1.0},  {1.0,-1.0,1.0},  {1.0,1.0,1.0},
  {1.0,1.0,1.0},  {1.0,-1.0,1.0},  {1.0,-1.0,-1.0},
  {1.0,1.0,1.0},  {1.0,-1.0,-1.0},  {1.0,1.0,-1.0},
  {1.0,-1.0,1.0},  {-1.0,-1.0,1.0},  {-1.0,-1.0,-1.0},
  {1.0,-1.0,1.0},  {-1.0,-1.0,-1.0},  {1.0,-1.0,-1.0},
  {1.0,1.0,-1.0},  {-1.0,1.0,-1.0},  {-1.0,1.0,1.0},
  {1.0,1.0,-1.0},  {-1.0,1.0,1.0},  {1.0,1.0,1.0},
  {-1.0,-1.0,-1.0},  {-1.0,1.0,-1.0},  {1.0,1.0,-1.0},
  {-1.0,-1.0,-1.0},  {1.0,1.0,-1.0},  {1.0,-1.0,-1.0},
  {-1.0,1.0,-1.0},  {-1.0,-1.0,-1.0},  {-1.0,-1.0,1.0},
  {-1.0,1.0,-1.0},  {-1.0,-1.0,1.0},  {-1.0,1.0,1.0}
};

//6 faces, 2 triangles/face, RGB colors
float v_colors[12][3] = {
  //color for face 1
  {1.0, 0.0, 0.0},  //triangle 1
  {1.0, 0.0, 0.0},  //triangle 2
  //color for face 2
  {0.0, 1.0, 0.0},
  {0.0, 1.0, 0.0},

  {0.0, 0.0, 1.0},
  {0.0, 0.0, 1.0},

  {1.0, 0.0, 1.0},
  {1.0, 0.0, 1.0},

  {0.0, 1.0, 1.0},
  {0.0, 1.0, 1.0},

  {1.0, 1.0, 0.0},
  {1.0, 1.0, 0.0},
};


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    y_angle-=offset;
    break;
    case GLUT_KEY_RIGHT :
    y_angle+=offset;
    break;
    case GLUT_KEY_UP :
    x_angle-=offset;
    break;
    case GLUT_KEY_DOWN :
    x_angle+=offset;
    break;
    case GLUT_KEY_PAGE_UP :
    z_angle-=offset;
    break;
    case GLUT_KEY_PAGE_DOWN :
    z_angle+=offset;
    break;
  }

  //Reset angles in range 0 to 360
  if(x_angle<0) {
    x_angle=x_angle+360;
  } else if(x_angle>360) {
    x_angle=x_angle-360;
  }

  if(y_angle<0){
    y_angle=y_angle+360;
  } else if(y_angle>360) {
    y_angle=y_angle-360;
  }

  if(z_angle<0){
    z_angle=z_angle+360;
  } else if(z_angle>360){
    z_angle=z_angle-360;
  }

  //Redraw
  glutPostRedisplay();
}


void drawBox(void)
{
  glPushMatrix();
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  glRotatef(z_angle, 0.0, 0.0, 1.0);

  for (int i=0;i<12;i++){
    glBegin(GL_TRIANGLES);
    glColor3fv(v_colors[i]);
    glVertex3fv(v_positions[3*i]);
    glVertex3fv(v_positions[3*i+1]);
    glVertex3fv(v_positions[3*i+2]);
    glEnd();
  }

  glPopMatrix();
}


void drawGradientBox(void)
{
  glPushMatrix();
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  glRotatef(z_angle, 0.0, 0.0, 1.0);

  for (int i=0;i<12;i++){
    glBegin(GL_TRIANGLES);
    glColor3fv(v_colors[i]);
    glVertex3fv(v_positions[3*i]);
    glColor3fv(v_colors[(i+1)%12]);
    glVertex3fv(v_positions[3*i+1]);
    glColor3fv(v_colors[(i+2)%12]);
    glVertex3fv(v_positions[3*i+2]);
    glEnd();
  }

  glPopMatrix();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //drawBox();
  drawGradientBox();
  //Swaps front buffer with back buffer
  glutSwapBuffers();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);

  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(40.0, 1.0, 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 8.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Color Cube Rotate");
  glutDisplayFunc(display);

  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);

  init();
  glutMainLoop();
  return 0;
}

/*
//For individual object rotation you will need glPushMatrix() & glPopMatrix();
glPushMatrix();
glTranslate(-originalX, -originalY, -originalZ);  //translate to origin
glRotate(angle, 0, 1, 0);
glTranslate(originalX, originalY, originalZ);     //translate back
...
glPopMatrix();
*/
