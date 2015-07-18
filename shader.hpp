#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "gl_util.hpp"

using namespace std;

class Shader
{
public:
    Shader();
    ~Shader();

    GLuint shaderID;
    GLuint loadFromFile(string, GLenum);
    GLuint createShader(GLenum);
    void deleteShader();

protected:
    void attachSource(GLuint,GLsizei, const GLchar**,const GLint*);
    void compile(GLuint, string);
    void printShaderLog(GLuint);
    void getShaderParam(GLuint,GLenum,GLint*);
    void getInfoLog(GLuint,  GLsizei, GLsizei*,  GLchar*);
};

class CreateShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glCreateShader() call.";
    }
};

class DeleteShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glDeleteShader() call.";
    }
};

class SourceShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glShaderSource() call.";
    }
};

class CompileShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] Shader::compile() call.";
    }
};

class LogShdEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] Shader::printShaderLog() call.";
    }
};

#endif