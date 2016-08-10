#include <GL/glut.h>
#include<iostream>
#include<vector>
#include "HNode.hpp"

using namespace std;


HNode *node[3];
int curr=0; //Index of current oprational node

//Divides the quard in two triangles and computes its vertex points
inline void quad(int a,int b,int c,int d,int idx,float (&corners)[8][4],float (&points)[36][4]){
  //Traingle 1
  vertexcopy(corners[a],points[idx]); idx++;
  vertexcopy(corners[b],points[idx]); idx++;
  vertexcopy(corners[c],points[idx]); idx++;
  //Traingle 2
  vertexcopy(corners[a],points[idx]); idx++;
  vertexcopy(corners[c],points[idx]); idx++;
  vertexcopy(corners[d],points[idx]);
}

//Forms the cuboid given its 8 corners and updates the points array
void makeCuboid(float (&corners)[8][4],float (&points)[36][4]) {
  int idx=0;
  //Face 1
  quad(0,1,2,3,idx,corners,points); idx+=6;
  //Face 2
  quad(4,5,6,7,idx,corners,points); idx+=6;
  quad(0,1,7,4,idx,corners,points); idx+=6;
  quad(1,2,6,7,idx,corners,points); idx+=6;
  quad(0,3,5,4,idx,corners,points); idx+=6;
  quad(2,3,5,6,idx,corners,points);
}


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
      curr=0;
      break;
    case '2':
      curr=1;
      break;
    case '3':
      curr=2;
      break;
  }
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    node[curr]->dec_ry();
    break;
    case GLUT_KEY_RIGHT :
    node[curr]->inc_ry();
    break;
    case GLUT_KEY_UP :
    node[curr]->dec_rx();
    break;
    case GLUT_KEY_DOWN :
    node[curr]->inc_rx();
    break;
    case GLUT_KEY_PAGE_UP :
    node[curr]->dec_rz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    node[curr]->inc_rz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  node[0]->render_tree();
  glutSwapBuffers();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 9.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  float v_positions[36][4];
  float v_colors[36][4];

  // float cube_corners[8][4]={
  //   {-1,-1,-1,1},
  //   {1,-1,-1,1},
  //   {1,1,-1,1},
  //   {-1,1,-1,1},
  //   {-1,-1,1,1},
  //   {-1,1,1,1},
  //   {1,1,1,1},
  //   {1,-1,1,1}
  // };
  // makeCuboid(cube_corners,v_positions);

  float cubiod_corners[8][4]={
    {0,-0.25,-0.25,1},
    {2,-0.25,-0.25,1},
    {2,0.25,-0.25,1},
    {0,0.25,-0.25,1},
    {0,-0.25,0.25,1},
    {0,0.25,0.25,1},
    {2,0.25,0.25,1},
    {2,-0.25,0.25,1}
  };
  makeCuboid(cubiod_corners,v_positions);

  float cubiod_corner_colors[8][4]={
    {0,1,0,1},
    {0,1,0,1},
    {1,0,1,1},
    {1,0,1,1},
    {1,0,0,1},
    {0,0,1,1},
    {0,0,1,1},
    {1,0,0,1}
  };
  makeCuboid(cubiod_corner_colors,v_colors);

  //Parent Node
  node[0] = new HNode(NULL,36,v_positions,v_colors);
  //Child Nodes
  node[1] = new HNode(node[0],36,v_positions,v_colors);
  node[1]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  node[2] = new HNode(node[1],36,v_positions,v_colors);
  node[2]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Hierarchical Modeling");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}
