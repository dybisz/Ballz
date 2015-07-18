/**
 * Class contains functions useful during OpenGL usage like e.g.
 * error handling or shaders loading.
 */

#ifndef __GL_UTIL__
#define __GL_UTIL__

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

#endif