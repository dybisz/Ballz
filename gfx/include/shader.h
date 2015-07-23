#ifndef GFX_INCLUDE_SHADER_H_
#define GFX_INCLUDE_SHADER_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "gl_util.h"

using namespace std;

// TODO(dybisz) verbose mode, which (when turned on) will say smth like
// TODO(dybisz) ... "compiling [name] shader: complete", where [name] will be
// TODO(dybisz) ... loaded e.g. from first comment in shader source.

class Shader
{

protected:
    GLuint createShader(GLenum);
    void deleteShader();
    void attachSource(GLuint,GLsizei, const GLchar**,const GLint*);
    void compile(GLuint, string);
    void printShaderLog(GLuint);
public:
    GLuint shaderID;
    GLuint loadFromFile(string, GLenum);
    Shader();
    ~Shader();
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