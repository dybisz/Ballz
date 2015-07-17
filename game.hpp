#ifndef __GAME__
#define __GAME__

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.hpp"
#include "error_const.hpp"
#include "config.hpp"

using namespace std;

class Game: public Drawable
{
public:
    Game();
    virtual ~Game();

    int render();
    int handleInput(Config* config, vector<Drawable*> states);
};

#endif