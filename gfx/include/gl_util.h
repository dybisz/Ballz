#ifndef GFX_INCLUDE_GL_UTIL_H_
#define GFX_INCLUDE_GL_UTIL_H_

#include <GL/glew.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>
#include "error_const.h"

// Determines whether error occurred using OpenGL API.
bool GL_error();

// Prints out to stdout OpenGL version.
void GL_print_version();

// TODO(dybisz) getProgramParam and switch it with glGetProgramiv in shader.cpp and shader_program.cpp
// Wraps up glGetShaderiv() routine with error check. No throws -
// error is just a suggestion that something went wrong.
void getShaderParam(GLuint shader,  GLenum pname,  GLint *params);

// Wraps up glGetShaderInfoLog() routine with error check. No throws -
// error is just a suggestion that something went wrong.
void getInfoLog(GLuint shader,  GLsizei  maxLength,  GLsizei * length,  GLchar * infoLog);

#endif