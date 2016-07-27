/*
 * This program draws a white triangle with the help of OpenGL
 *
 * Reference : http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
 *             https://www.opengl.org/sdk/docs/man2/xhtml/
 */

//#include <GLUT/glut.h>	//Include for MAC
#include <GL/glut.h>	//Include for Linux

void yourRenderFunction(void) {

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	//For other types you may refer to https://www.opengl.org/sdk/docs/man2/xhtml/glBegin.xml
	//But we will only use Lines and Triangles since other primitives are depricated since OpenGL v3.1
	glVertex3f(0.0f,  0.5f, 0.0f); // Vertex of 3 floats viz. x, y & z
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f,-0.5f, 0.0f);
	glEnd();

	// Swap front and back buffers
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Title : Triangle");

	// register callbacks
	glutDisplayFunc(yourRenderFunction);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
