#ifndef __BALL__
#define __BALL__

#define PI 3.14159265

#include "shader.hpp"
#include <vector>
#include <math.h>
#include "drawable.hpp"
#include "config.hpp"
#include "shader_program.hpp"
#include <GL/gl.h>
#include "buffer_object.hpp"

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

//TODO option for taking precompiled program/shaders from the outside - when one program
//TODO      is used to render many balls e.g. Smth like setProgram / setVertShader set FragShader
//TODO      with appropriate handling.

class Ball
{

private:
    static const int RINGS;
    static const int SECTORS;
    static const int DATA_PER_VERTEX;
    static const int DATA_PER_QUAD;
    static const string FRAGMENT_SHADER_PATH;
    static const string VERTEX_SHADER_PATH;
    void generateVertices(float);
    void generateIndices();
    glm::mat4 mModel;
    glm::mat4 mView;
    glm::mat4 mProjection;
    vector<GLfloat> vertices;
    vector<GLuint> indices;
    BufferObject vbo;
    BufferObject indices_vbo;

public:
    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram program;
    void setView(glm:: mat4);
    void setProjection(glm:: mat4);
    int render();
    int handleInput(Config* config, vector<Drawable*> states);

    Ball();
    ~Ball();
};

#endif