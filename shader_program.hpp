#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <GL/glew.h>
#include <GL/gl.h>
#include <exception>
#include <iostream>
#include <stdio.h>
#include "gl_util.hpp"

using namespace std;

class ShaderProgram
{
private:
    void createProgram();
    void deleteProgram();
    void attachShader(GLuint);
    void linkProgram();
    void printProgramLog(GLuint);

public:
    GLuint programID;
    void attachShaders(GLuint, GLuint);

    ShaderProgram();
    ~ShaderProgram();
};

class CreateProgEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glCreateProgram() call.";
    }
};

class DeleteProgEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glDeleteProgram() call.";
    }
};

class AttachShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glAttachShader call.";
    }
};

class LinkProgEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glLinkProgram call.";
    }
};

class LogProgEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] ShaderProgram::printProgramLog() call.";
    }
};
#endif