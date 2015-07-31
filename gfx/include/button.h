#ifndef GFX_INCLUDE_BUTTON_H_
#define GFX_INCLUDE_BUTTON_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/freeglut.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <vector>
#include "drawable.h"
#include "error_const.h"
#include "config.h"
#include "point.h"
#include "window_content.h"
#include <string>
#include <functional>
#include "color.h"



#define BUTTON_DEPTH_NOT_PRESSED 0.0
#define BUTTON_DEPTH_PRESSED -2.0


/*static const struct Color BUTTON_COLOR_NORMAL = { 0.3, 0.2, 0.6 };
static const struct Color BUTTON_COLOR_PRESSED = {0.1, 0.3,0.5};
static const struct Color BUTTON_COLOR_HOOVER = {0.6,0.3,0.1};*/

using namespace std;

class Button{
public:
    Point *leftTop,*leftBottom,*rightTop,*rightBottom;
    float width,height;
    string content;
    Config* config = NULL;
    WindowContent* windowContent =NULL;
    Color* buttonColor;
    GLfloat buttonDepth;



    Button(std::string content, float xPos, float yPos, float width, float height,Config* config, WindowContent* windowConent );
    Button(std::string content, float xPos, float yPos, float width, float height,Config* config, WindowContent* windowConent,float fontSize, Color* fontColor);

    //Handles events and set the button's sprite region
    void handle_events(SDL_Event* event);

    //Function drawing button
    void draw();

    //Function setting the behavior after button click
    void setButtonClick(function<void(Config* config, WindowContent* windowContent)> func);
    function<void(Config* config, WindowContent* windowContent)> buttonClick;

    void setButtonColorNormal(float r, float g, float b);

    void setButtonColorPressed(float r, float g, float b);

    void setButtonColorHoover(float r, float g, float b);


private:
    void renderText();
    // fontSize range: 1-50
    float fontSize;
    Color* fontColor;

    Color* buttonColorNormal = new Color( 0.3, 0.2, 0.6);
    Color* buttonColorPressed = new Color(0.1, 0.3,0.5);
    Color* buttonColorHoover = new Color(0.6,0.3,0.1);

};

#endif
