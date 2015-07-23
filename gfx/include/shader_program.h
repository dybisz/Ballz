#ifndef GFX_INCLUDE_SHADER_PROGRAM_H_
#define GFX_INCLUDE_SHADER_PROGRAM_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <exception>
#include <iostream>
#include <string>
#include <stdio.h>
#include "gl_util.h"

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace std;

// TODO(dybisz) program as a pointer to check if it has been created or not

// TODO(dybisz) createProgram call only when it is needed i.e. attachShaders or useProgram etc.
// TODO(dybisz) ... This will prevent creating n programs for e.g. n balls when balls will
// TODO(dybisz) ... be rendered using 1 external program.

// TODO(dybisz) Decide if all (or most) possible shaders would use standard variables for
// TODO(dybisz) ... uModel, uView, uProjection, aPosition, vColor etc.

class ShaderProgram
{
private:
    static const GLchar* UNIFORM_MODEL_MATRIX;
    static const GLchar* UNIFORM_VIEW_MATRIX;
    static const GLchar* UNIFORM_PROJECTION_MATRIX;
    static const GLchar* UNIFORM_CAMERA_POSITION;
    static const GLchar* ATTRIBUTE_POSITION;
    static const GLchar* ATTRIBUTE_NORMAL;
    /**
    * Method calls glCreateProgram() and throws appropriate exception when needed.
    */
    void _createProgram();

    /**
    * Calls glDeleteProgram and check for errors.
    */
    void _deleteProgram();
    void _attachShader(GLuint);
    void _linkProgram();
    void _useProgram();
    void _printProgramLog(GLuint);
    GLuint _getUniform(const GLchar*);
    void _setUniformMatrix(GLint,GLsizei,GLboolean,const GLfloat*);

public:
    GLuint programID;
    /**
    * Attaches provided shaders to the program and links it.
    */
    void attachShaders(GLuint, GLuint);
    void setModelMatrix(glm::mat4);
    void setViewMatrix(glm::mat4);
    void setProjectionMatrix(glm::mat4);
    void setCameraPosition(glm::vec3);
    void setVertices(GLuint bufferID);
    void setNormals(GLuint bufferID);
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