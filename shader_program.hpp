#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <GL/glew.h>
#include <GL/gl.h>
#include <exception>
#include <iostream>
#include <string>
#include <stdio.h>
#include "gl_util.hpp"

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>

using namespace std;

//TODO program as a pointer to check if it has been created or not

//TODO createProgram call only when it is needed i.e. attachShaders or useProgram etc.
//TODO      This will prevent creating n programs for e.g. n balls when balls will
//TODO      be rendered using 1 external program.

//TODO Decide if all (or most) possible shaders would use standard variables for
//TODO      uModel, uView, uProjection, aPosition, vColor etc.

class ShaderProgram
{
private:
    static const GLchar* UNIFORM_MODEL_MATRIX;
    static const GLchar* UNIFORM_VIEW_MATRIX;
    static const GLchar* UNIFORM_PROJECTION_MATRIX;
    static const GLchar* ATTRIBUTE_POSITION;
    void createProgram();
    void deleteProgram();
    void attachShader(GLuint);
    void linkProgram();
    void printProgramLog(GLuint);
    GLuint getUniform(const GLchar*);
    void setUniformMatrix(GLint,GLsizei,GLboolean,const GLfloat*);

public:
    GLuint programID;
    void attachShaders(GLuint, GLuint);
    void setModelMatrix(glm::mat4);
    void setViewMatrix(glm::mat4);
    void setProjectionMatrix(glm::mat4);
    void setVertices(GLuint bufferID);
    void useProgram();
    void stopProgram();

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

class UniformLocationEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glGetUniformLocation() call.";
    }
};

class SetUniformMatEx: public exception
{
    virtual const char* what() const throw()
    {
        return "[Error] glUniformMatrix4fv() call.";
    }
};
#endif