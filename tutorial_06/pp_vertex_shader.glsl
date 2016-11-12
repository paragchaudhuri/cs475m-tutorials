#version 120

varying vec4 glCol;
varying vec4 glVer;
varying vec3 glNor;

void main (void) 
{
	
  //Internal variables
  //gl_Position : location of the vertex on the screen
  //gl_ModelViewProjectionMatrix : stores the product of 
  //   projection * view * model matrices 
  //gl_Vertex : location of vertex passed by glVertex***()
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 

  // Normals = Orientation * NormalInWCS
  // Normal matrix = transpose(inverse(mat3(ModelView matrix)));
  glNor = normalize(gl_NormalMatrix * gl_Normal);

	// Vertex in view co-ordinate system 
  //(for use in fragment shader)
  glVer = gl_ModelViewMatrix * gl_Vertex;

	//Just pass the colour as it is
  glCol = gl_Color;
}

