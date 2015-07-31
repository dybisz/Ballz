#ifndef GFX_INCLUDE_TEXT_BOX_H_
#define GFX_INCLUDE_TEXT_BOX_H_

#include <string>
#include "point.h"
#include "config.h"
#include "window_content.h"
#include "color.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <SDL2/SDL.h>
using namespace std;

/*static const struct Color BUTTON_COLOR_NORMAL = { 0.3, 0.2, 0.6 };
static const struct Color BUTTON_COLOR_PRESSED = {0.1, 0.3,0.5};
static const struct Color BUTTON_COLOR_HOOVER = {0.6,0.3,0.1};*/

class TextBox{

public:
    /*
     * FIELDS
     */
    Point *leftTop,*leftBottom,*rightTop,*rightBottom;
    float width,height;
    string text;
    Config* config = NULL;
    WindowContent* windowContent =NULL;
    Color* textBoxColor;
    bool isEditingEnabled = true;
    float opacity = 1.0f;

    /*
     * CONSTRUCTORS
     */
    TextBox(float xPos, float yPos, float width, float height,Config* config, WindowContent* windowConent );

    /*
     * OTHER METHODS
     */
    void draw();
    //Handles events and set the button's sprite region
    void handle_events(SDL_Event* event);

private:
    void renderText();
    // fontSize range: 1-50
    float fontSize;
    Color* fontColor;
    bool isInputActive = false;

    Color* textBoxColorNormal = new Color(0.3, 0.2, 0.6);
    Color* textBoxColorPressed = new Color(0.1, 0.3,0.5);
    Color* textBoxColorHoover = new Color(0.6,0.3,0.1);
};

#endif