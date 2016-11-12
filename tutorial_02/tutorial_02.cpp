/*
 * Reference: https://www.opengl.org/archives/resources/code/samples/glut_examples/examples/examples.html
 */

#ifdef __APPLE__
#include <GLUT/glut.h>  //Include for MAC
#endif
#ifndef __APPLE__
#include <GL/glut.h>
#endif

using namespace std;

//6 faces, 2 triangles/face, 3 vertices/triangle = 36 , each point in 3 dimension {x,y,z}
float v_positions[36][3] = {
//Face 1
//triangle 1
{-1.0,1.0,1.0},
{-1.0,-1.0,1.0},
{1.0,-1.0,1.0},
//triangle 2
{-1.0,1.0,1.0},
{1.0,-1.0,1.0},
{1.0,1.0,1.0},

//Face 2
//triangle 1
{1.0,1.0,1.0},
{1.0,-1.0,1.0},
{1.0,-1.0,-1.0},
//triangle 2
{1.0,1.0,1.0},
{1.0,-1.0,-1.0},
{1.0,1.0,-1.0},

{1.0,-1.0,1.0},
{-1.0,-1.0,1.0},
{-1.0,-1.0,-1.0},

{1.0,-1.0,1.0},
{-1.0,-1.0,-1.0},
{1.0,-1.0,-1.0},

{1.0,1.0,-1.0},
{-1.0,1.0,-1.0},
{-1.0,1.0,1.0},

{1.0,1.0,-1.0},
{-1.0,1.0,1.0},
{1.0,1.0,1.0},

{-1.0,-1.0,-1.0},
{-1.0,1.0,-1.0},
{1.0,1.0,-1.0},

{-1.0,-1.0,-1.0},
{1.0,1.0,-1.0},
{1.0,-1.0,-1.0},

{-1.0,1.0,-1.0},
{-1.0,-1.0,-1.0},
{-1.0,-1.0,1.0},

{-1.0,1.0,-1.0},
{-1.0,-1.0,1.0},
{-1.0,1.0,1.0}
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

void drawBox(void)
{
  for (int i=0;i<12;i++){
    glBegin(GL_TRIANGLES);
    glColor3fv(v_colors[i]);
    glVertex3fv(v_positions[3*i]);
    glVertex3fv(v_positions[3*i+1]);
    glVertex3fv(v_positions[3*i+2]);
    glEnd();
  }
}

//You may draw a gradient triangle by giving different colors to different vertices
void drawGradientBox()
{
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
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  //drawGradientBox();  //Uncomment this and comment call to drawBox()
  glutSwapBuffers();
}

//We will learn more about viewing in the later tutorials, for now dont worry
// much about the the functions used in init() function
void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);

  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(40.0, 1.0, 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  // eye is at (0,0,5)
    0.0, 0.0, 0.0,      // center is at (0,0,0)
    0.0, 1.0, 0.);      // up is in positive Y direction

  //Adjust cube position to be asthetic angle.
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-120, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Color Cube");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}
