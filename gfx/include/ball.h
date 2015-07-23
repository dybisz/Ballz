#ifndef GFX_INCLUDE_BALL_H_
#define GFX_INCLUDE_BALL_H_

#define PI 3.14159265
// TODO(dybisz) change in code PI to M_PI from math.h and delete PI

#include "shader.h"
#include <vector>
#include <math.h>
#include "drawable.h"
#include "config.h"
#include "shader_program.h"
#include <GL/gl.h>
#include "buffer_object.h"

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// TODO(dybisz) option for taking precompiled program/shaders from the outside - when one program
// TODO(dybisz) ... is used to render many balls e.g. Smth like setProgram / setVertShader set FragShader
// TODO(dybisz) ... with appropriate handling.

class Ball {
 private:
    static const int RINGS;
    static const int SECTORS;
    static const int DATA_PER_VERTEX;
    static const int DATA_PER_NORMAL;
    static const int DATA_PER_QUAD;
    static const string FRAGMENT_SHADER_PATH;
    static const string VERTEX_SHADER_PATH;

    void generateVerticesAndNormals(float);

    void generateIndices();

    glm::mat4 mModel;
    glm::mat4 mView;
    glm::mat4 mProjection;
    glm::vec3 vCameraPosition;
    vector <GLfloat> vertices;
    vector <GLfloat> normals;
    vector <GLuint> indices;
    BufferObject bVertices;
    BufferObject bNormals;
    BufferObject bIndices;
 public:
    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram program;

    void setView(glm::mat4);

    void setProjection(glm::mat4);

    void setCameraPosition(glm::vec3);

    int render();

    int handleInput(Config *config, vector<Drawable *> states);

    Ball();

    ~Ball();
};

#endif
