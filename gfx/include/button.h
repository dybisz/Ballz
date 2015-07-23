#ifndef GFX_INCLUDE_BUTTON_H_
#define GFX_INCLUDE_BUTTON_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.h"
#include "error_const.h"
#include "config.h"
#include "point.h"
#include <string>

#define BUTTON_DEPTH_NOT_PRESSED 0.0
#define BUTTON_DEPTH_PRESSED -2.0

typedef struct Color{
    float r;
    float g;
    float b;
} Color;

static const struct Color BUTTON_COLOR_NORMAL = { 0.3, 0.2, 0.6 };
static const struct Color BUTTON_COLOR_PRESSED = {0.1, 0.3,0.5};
static const struct Color BUTTON_COLOR_HOOVER = {0.6,0.3,0.1};

using namespace std;

class Button{
public:
    Point *leftTop,*leftBottom,*rightTop,*rightBottom;
    Config* config;
    Color buttonColor;
    GLfloat buttonDepth;



    Button(std::string content, float xPos, float yPos, float width, float height,Config* config );

    //Handles events and set the button's sprite region
    void handle_events(SDL_Event* event);
    void draw();

    //void buttonClickHandler(const function<void ()>& f);

private:
    //function<void()> button_click_handle_function;
};

#endif