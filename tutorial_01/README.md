## INTRODUCTION
This is a simple tutorial on OpenGL using freeglut. This program will open a window and render a triangle in it.

## INSTALATION
On ubuntu system just install the freeglut package using your terminal. For other operating system please use the corresponding package installer like yum or brew. <br>
`$ sudo apt-get install freeglut3-dev`

## COMPILATION
You can either use the given makefile for compilation or use the following command. But learn to use makefile. <br>
`$ make`    <br>
OR          <br>
`$ g++ 01_triangle.cpp -o 01_triangle -lglut -lGLU -lGL -lm`

## RUN
After successfull compilation just type the following command in your terminal to execute the binary.<br>
`$ ./01_triangle` <br>
By now, if every thing went well you must see a window with a white triangle in it.

## REFERENCES
http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
