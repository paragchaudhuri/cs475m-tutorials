/*
*/

#include "GLShaderUtils.h"
#ifdef __APPLE__
#include <GLUT/glut.h>  //Include for MAC
#endif
#ifndef __APPLE__
#include <GL/glut.h>
#endif
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>

using namespace std;

float x_angle=0.0;
float y_angle=0.0;
float z_angle=0.0;
float offset=5.0;
int sphere_tessellation=8;

bool sphericalNormals=false;
bool wire=true;

 GLfloat black[] = {0,0,0,1};
 GLfloat white[] = {1,1,1,1};
 GLfloat cyan[] = {0,1,1,1};

enum ObjectType {CUBE, SPHERE, TEAPOT};
ObjectType active_object = CUBE;

enum ShaderType {FLAT, GOURAUD, PERPIXEL};
ShaderType active_shader = FLAT;

GLuint pps_program;
GLuint l1p_g, l1p_pps, l1c_g, l1c_pps;

GLfloat l1_pos[]={1.0f,1.0f,1.2f,1.0f}; //Try changing light position
GLfloat l1_col[]={1.0f,1.0f,1.0f,1.0f};

//TODO
//Try passing material (diffuse, specular) properties to shaders, in the similar manner, as we did for light pos and col.
GLfloat light_ambient[]={0.05, 0.05, 0.05, 1.0};//0.7, 0.7, 0.5, 1.0};
GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};//0.7, 0.7, 0.5, 1.0};
GLfloat light_specular[]={0.1, 0.1, 0.1, 1.0};//{1.0, 0.0, 0.0, 1.0};

/*
https://www.opengl.org/wiki/Calculating_a_Surface_Normal
So for a triangle p1, p2, p3, if the vector U = p2 - p1 and the vector V = p3 - p1 then the normal N = U X V and can be calculated by:
Nx = UyVz - UzVy
Ny = UzVx - UxVz
Nz = UxVy - UyVx
*/
//Note that we can also take help of OpenGL Mathematics library (glm) insted of doing it manually.
float* getTriangleNormal(float p1[4],float p2[4],float p3[4]){
  float *N = new float[4];
  float Ux,Uy,Uz;
  float Vx,Vy,Vz;
  //Vector Subtraction
  Ux=p2[0]-p1[0];
  Uy=p2[1]-p1[1];
  Uz=p2[2]-p1[2];

  Vx=p3[0]-p1[0];
  Vy=p3[1]-p1[1];
  Vz=p3[2]-p1[2];
  //Cross Product of U & V (UxV)
  N[0] = Uy*Vz - Uz*Vy;
  N[1] = Uz*Vx - Ux*Vz;
  N[2] = Ux*Vy - Uy*Vx;
  N[3] = 1.0f;

  //Normalize
  float magnitude = sqrt(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]);
  N[0]= N[0]/magnitude;
  N[1]= N[1]/magnitude;
  N[2]= N[2]/magnitude;

  return N;
}



void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
  dest[3]=src[3];
}


//Divides the quard in two triangles and computes its vertex points
inline void quad(int a,int b,int c,int d,int idx,float (&corners)[8][4],float (&points)[36][4], float (&pointNormals)[36][4]){
  //Traingle 1
  float *N =  getTriangleNormal(corners[a],corners[b],corners[c]);
  vertexcopy(corners[a],points[idx]); vertexcopy(N,pointNormals[idx]); idx++;
  vertexcopy(corners[b],points[idx]); vertexcopy(N,pointNormals[idx]); idx++;
  vertexcopy(corners[c],points[idx]); vertexcopy(N,pointNormals[idx]); idx++;
  delete N;

  //Traingle 2
  N =  getTriangleNormal(corners[a],corners[c],corners[d]);
  vertexcopy(corners[a],points[idx]); vertexcopy(N,pointNormals[idx]); idx++;
  vertexcopy(corners[c],points[idx]); vertexcopy(N,pointNormals[idx]); idx++;
  vertexcopy(corners[d],points[idx]); vertexcopy(N,pointNormals[idx]);
  delete N;
}

//Forms the cuboid given its 8 corners and updates the points array
void makeCuboid(float (&corners)[8][4],float (&points)[36][4], float (&pointNormals)[36][4]) {
  int idx=0;
  //Face 1
  quad(0,3,2,1,idx,corners,points,pointNormals); idx+=6;
  quad(4,7,6,5,idx,corners,points,pointNormals); idx+=6;
  quad(1,7,4,0,idx,corners,points,pointNormals); idx+=6;
  quad(2,6,7,1,idx,corners,points,pointNormals); idx+=6;
  quad(3,0,4,5,idx,corners,points,pointNormals); idx+=6;
  quad(2,3,5,6,idx,corners,points,pointNormals);
}



//6 faces, 2 triangles/face, 3 vertices/triangle = 36 , each point in 3 dimension {x,y,z}
float v_positions[36][4];
//Normals for each vertex
float v_normals[36][4];
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
  switch(key) {
    case 'g' : //Enable gouraud Shading
    active_shader = GOURAUD;
    break;
    case 'p' : //Enable PerPixel Shaders
		active_shader = PERPIXEL;
    break;
    case 'f' : //Enable Flat Shading
		active_shader = FLAT;
    break;
    case 's' : //draw sphare
    active_object = SPHERE;
    break;
    case 'c' : //draw cube
    active_object = CUBE;
    break;
    case 't' : //draw teapot
    active_object = TEAPOT;
    break;
    case 'n' : //toggle spherical Normals for cube
    sphericalNormals = !sphericalNormals;
    break;
    case 'w' : //toggle wireframe
    wire = !wire;
    break;

    case '+' : //increment tessellation
    sphere_tessellation++;
    break;
    case '-' : //decrement tessellation
    sphere_tessellation--;
    break;
    case 27://escape
    exit(0);
  }

  if(active_shader == PERPIXEL){
    glUseProgram(pps_program);
    glUniform4fv(l1c_pps,1,l1_col);
    glUniform4fv(l1p_pps,1,l1_pos);
  } else {
    glUseProgram(0); //Disable shaders (Enable fixed function pipeline)
    if (active_shader == FLAT){
      glShadeModel(GL_FLAT); //FLAT shading
    } else { 
      glShadeModel(GL_SMOOTH); //GOURAUD shading
    }
  }
  glutPostRedisplay();
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

void applyTransformation(){
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  glRotatef(z_angle, 0.0, 0.0, 1.0);
}

void drawSphere(void){

 //GLfloat black[] = {0,0,0,1};
 //GLfloat white[] = {1,1,1,1};
  glPushMatrix();
  applyTransformation();
  glColor4fv(white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
  glutSolidSphere(1, sphere_tessellation, sphere_tessellation);

  if(wire){
    glColor4fv(black);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	 glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
   glutWireSphere(1.01, sphere_tessellation, sphere_tessellation);
  }

  glPopMatrix();
}

void drawTeapot(){

 //Material colour is same as defined by glColor***() thus we don't need to define glMaterialfv() as we are doing for cube and sphere.
 glEnable(GL_COLOR_MATERIAL);

 glPushMatrix();
 applyTransformation();
  glColor4fv(cyan);
	//NOT required since GL_COLOR_MATERIAL is enabled
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyan);
 glutSolidTeapot(1);

 if(wire){
  glColor4fv(black);
  glutWireTeapot(1.01);
 }

glDisable(GL_COLOR_MATERIAL);
 glPopMatrix();
}

void drawBox(void)
{
  glPushMatrix();
  applyTransformation();

  for (int i=0;i<12;i++){
    glBegin(GL_TRIANGLES);
    glColor3fv(v_colors[i]);

		//Set colours for GL_LIGHTING
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, v_colors[i]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v_colors[i]);


    if(sphericalNormals){
      //It is incorrect to give normal in same as direction as of vertex for a cube
      //This will produce incorrect lighting effect. 
			//So spherical normals are incorrect way to light up a cube.
      glNormal3fv(v_positions[3*i]);
    }else{
      glNormal3fv(v_normals[3*i]);
    }
    glVertex3fv(v_positions[3*i]);

    if(sphericalNormals){
      glNormal3fv(v_positions[3*i+1]);
    }else{
      glNormal3fv(v_normals[3*i+1]);
    }
    glVertex3fv(v_positions[3*i+1]);

    if(sphericalNormals){
      glNormal3fv(v_positions[3*i+2]);
    }else{
      glNormal3fv(v_normals[3*i+2]);
    }
    glVertex3fv(v_positions[3*i+2]);
    glEnd();
  }

  glPopMatrix();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(active_object == SPHERE){
    drawSphere();
  } else if(active_object == CUBE){
    drawBox();
  } else {
    drawTeapot();
  }
  glutSwapBuffers();
}

void init(void)
{
  glEnable(GL_NORMALIZE);

  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  // Setup the view
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(40.0, 1.0, 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 6.0,  // eye is at (0,0,6)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction


  glEnable(GL_LIGHT0);

  glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  
  GLfloat global_ambient[] = {0.0,0.0,0.0,1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient); 

  glMaterialf(GL_FRONT, GL_SHININESS, 1000.0f);


  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);
  glLightfv(GL_LIGHT0, GL_POSITION, l1_pos);

  //Move light to View Co-ordinate System (for per-pixel shading only)
  float mv[16];
  float tmp[4];
  //GL_MODELVIEW_MATRIX currently holds the LookAt matrix only
  glGetFloatv(GL_MODELVIEW_MATRIX,mv); //Column major order
  //Light Position in View Co-ordinate System = GL_MODELVIEW_MATRIX * Light Position in World Co-ordinate System
  tmp[0]=l1_pos[0]*mv[0]+l1_pos[1]*mv[4]+l1_pos[2]*mv[8]+l1_pos[3]*mv[12];
  tmp[1]=l1_pos[0]*mv[1]+l1_pos[1]*mv[5]+l1_pos[2]*mv[9]+l1_pos[3]*mv[13];
  tmp[2]=l1_pos[0]*mv[2]+l1_pos[1]*mv[6]+l1_pos[2]*mv[10]+l1_pos[3]*mv[14];
  tmp[3]=l1_pos[0]*mv[3]+l1_pos[1]*mv[7]+l1_pos[2]*mv[11]+l1_pos[3]*mv[15];
  vertexcopy(tmp,l1_pos); //update ligth position


  pps_program = LoadShader("pp_vertex_shader.glsl", "pp_fragment_shader.glsl");
  l1c_pps = glGetUniformLocation(pps_program,"light_color");
  l1p_pps = glGetUniformLocation(pps_program,"lightPos");

}

int main(int argc, char **argv)
{
  float cube_corners[8][4]={
    {-1,-1,-1,1},
    {1,-1,-1,1},
    {1,1,-1,1},
    {-1,1,-1,1},
    {-1,-1,1,1},
    {-1,1,1,1},
    {1,1,1,1},
    {1,-1,1,1}
  };
  makeCuboid(cube_corners,v_positions,v_normals);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("SHading Tutorial");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  #ifndef __APPLE__
  glewInit();
  #endif
  init();

  #ifndef __APPLE__
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)) {
    cout<<"Shaders (GLSL) not supported."<<endl;
    exit(1);
  }
  #endif

  glutMainLoop();
  return 0;
}
