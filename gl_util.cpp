#include "gl_util.hpp"

bool GL_error()
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf( "[Error] %s\n", gluErrorString(error));
        return true;
    }
    else return false;
}

void GL_print_version()
{
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
}