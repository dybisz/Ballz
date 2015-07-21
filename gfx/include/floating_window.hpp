#ifndef __FLOATING_WINDOW__
#define __FLOATING_WINDOW__

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.hpp"
#include "error_const.hpp"
#include "config.hpp"
#include "point.hpp"
#include <string>

using namespace std;

class FloatingWindow{
public:
    /*
     * Fields
     */
    Point *leftTop,*leftBottom,*rightTop,*rightBottom;
    Config* config;
    float topBarHeight;

    /*
     * window movement
     */
    bool mouseDown;
    Point* mouseCoords;
    /*
     * Constructors
     */
    FloatingWindow(float width, float height,Config* config);

    /*
     * Methods
     */
    void handle_events(SDL_Event* event);
    void draw();
};

#endif