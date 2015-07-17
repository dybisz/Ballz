#include "gl_util.hpp"

bool GL_error()
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return true;
    }
    else return false;
}