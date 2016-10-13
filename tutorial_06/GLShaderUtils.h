#ifndef _SHADER_UTIL_HPP_
#define _SHADER_UTIL_HPP_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


// namespace csX75
// {
  GLuint LoadShader(const std::string vertex_shader_file, const std::string fragment_shader_file);
  GLuint LoadShaderGL(GLenum eShaderType, const std::string &strFilename);
  GLuint CreateShaderGL(GLenum eShaderType, const std::string &strShaderFile);
  GLuint CreateProgramGL(const std::vector<GLuint> &shaderList);
// };

#endif
