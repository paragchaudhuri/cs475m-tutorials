#version 120

// Variables set from C++ code
uniform vec4 lightPos;
uniform vec4 light_color;

//Variables passed from vertex shader
varying vec4 glCol;
varying vec4 glVer;
varying vec3 glNor;

void main (void) 
{
  // Defining Materials 
  // (try passing material properties from C++ code)
  vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0); 
  vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0);
  vec4 specular = vec4(0.1, 0.1, 0.1, 1.0);
  float shininess = 100;
  vec4 spec = vec4(0.0); 
  
  // Defining Light 
  // LightDirection (L) = LightPositionInVCS - VertexPositionInVCS
  vec3 lightDir = normalize(vec3(lightPos - glVer)); 
  
  //Calculate Diffuse Component
  vec3 n = glNor;
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec4 eye = glVer;
	vec3 v = vec3(-eye);	//View vector (opposite direction of eye)
	vec3 h = normalize(lightDir + v ); //Half vector
   	float intSpec = max(dot(h,n), 0.0);	
        spec = specular * pow(intSpec, shininess);
  }  	
  
  //Final color 
  gl_FragColor = (intensity * diffuse  + spec + ambient) * glCol * light_color; // All
     
//-------No Lights-----------
//gl_FragColor = glCol;
}
