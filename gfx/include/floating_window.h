#ifndef GFX_INCLUDE_FLOATING_WINDOW_H_
#define GFX_INCLUDE_FLOATING_WINDOW_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.h"
#include "error_const.h"
#include "config.h"
#include "point.h"
#include <string>
#include <button.h>
#include "text_box.h"
using namespace std;

class FloatingWindow{
public:
    /*
     * Fields
     */
    Point *leftTop,*leftBottom,*rightTop,*rightBottom;
    Config* config;
    float topBarHeight;
    vector<Button*>* buttonVector = NULL;
    vector<TextBox*>* textBoxVector = NULL;
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

    void addChild(Button* button);
    void addChild(TextBox* textBox);

    void moveChild(Button* button, float x, float y);
    void moveChild(TextBox* textBox, float x, float y);
};

#endif