/**
 * Class contains functions useful during OpenGL usage like e.g.
 * error handling or shaders loading.
 */

#ifndef __GL_UTIL__
#define __GL_UTIL__

#include <GL/glew.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>
#include "error_const.hpp"

/**
 * Determines whether error occurred using OpenGL API.
 */
bool GL_error();

/**
 * Prints out to stdout OpenGL version.
 */
void GL_print_version();
//TODO getProgramParam and switch it with glGetProgramiv in shader.cpp and shader_program.cpp
/**
 * Wraps up glGetShaderiv() routine with error check. No throws -
 * error is just a suggestion that something went wrong.
 */
void getShaderParam(GLuint shader,  GLenum pname,  GLint *params);

/**
 * Wraps up glGetShaderInfoLog() routine with error check. No throws -
 * error is just a suggestion that something went wrong.
 */
void getInfoLog(GLuint shader,  GLsizei  maxLength,  GLsizei * length,  GLchar * infoLog);

#endif