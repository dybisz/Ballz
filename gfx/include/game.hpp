#ifndef __GAME__
#define __GAME__


#include <SDL2/SDL.h>
#include <vector>
#include "drawable.hpp"
#include "error_const.hpp"
#include "config.hpp"
#include "ball.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include "shader_program.hpp"
#include "perspective_cam.hpp"

using namespace std;

class Game: public Drawable
{
public:
    Game();
    virtual ~Game();

    int render();
    int handleInput(Config* config, vector<Drawable*> states);
    Ball ball;
    PerspectiveCamera devCamera;
};

#endif