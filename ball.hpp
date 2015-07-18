#ifndef __BALL__
#define __BALL__



#include "shader.hpp"
#include <vector>
#include "drawable.hpp"
#include "config.hpp"

#include "shader_program.hpp"
#include <GL/gl.h>
using namespace std;

class Ball
{

private:
    static const string FRAGMENT_SHADER_PATH;
    static const string VERTEX_SHADER_PATH;

public:
    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram program;

    Ball();
    ~Ball();
    int render();
    int handleInput(Config* config, vector<Drawable*> states);

};

#endif