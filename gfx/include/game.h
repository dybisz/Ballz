#ifndef GFX_INCLUDE_GAME_H_
#define GFX_INCLIDE_GAME_H_


#include <SDL2/SDL.h>
#include <vector>
#include "drawable.h"
#include "error_const.h"
#include "config.h"
#include "ball.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "shader_program.h"
#include "perspective_cam.h"
#include "terrain.h"

using namespace std;

class Game: public Drawable
{
private:
    static const float SCROLL_SPEED;
    int lastClickedX;
    int lastClickedY;
public:
    Game();
    virtual ~Game();

    int render();
    int handleInput(Config* config, vector<Drawable*> states);
    Ball ball;
    Terrain terrain_;
    PerspectiveCamera devCamera;
};

#endif