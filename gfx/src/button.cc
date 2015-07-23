#include "button.h"

Button::Button(std::string content, float xPos, float yPos, float width, float height,Config* config) {
    leftTop = new Point(xPos,yPos);
    leftBottom = new Point(xPos,yPos+height);
    rightTop = new Point(xPos+width,yPos);
    rightBottom = new Point(xPos+width,yPos+height);
    buttonColor = BUTTON_COLOR_NORMAL;
    buttonDepth = BUTTON_DEPTH_NOT_PRESSED;
    this->config = config;

}

void Button::handle_events(SDL_Event* event) {
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if( event->type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event->motion.x;
        y = event->motion.y;
        // printf("%d:%d\n",x,y);
        //If the mouse is over the button
        if( ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftTop->y+1.0f)/2* config->screenHeight) ) )
        {
            buttonColor = BUTTON_COLOR_HOOVER;
        }
            //If not
        else
        {
            buttonColor = BUTTON_COLOR_NORMAL;
        }
    }
    //If a mouse button was pressed
    if( event->type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event->button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event->button.x;
            y = event->button.y;

            //If the mouse is over the button
            if( ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftTop->y+1.0f)/2* config->screenHeight) ) )
            {
                //Set the button sprite
                buttonColor = BUTTON_COLOR_PRESSED;
                buttonDepth = 1.0f;
               // button_click_handle_function();
            }
        }
    }
    //If a mouse button was released
    if( event->type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event->button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event->button.x;
            y = event->button.y;

            //If the mouse is over the button
            if( ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftTop->y+1.0f)/2* config->screenHeight) ) )
            {
                //Set the button sprite
                buttonColor = BUTTON_COLOR_HOOVER;
            }
        }
    }

}

void Button::draw() {
    glBegin(GL_POLYGON);
    glMatrixMode(GL_PROJECTION);
    glColor3f(buttonColor.r,buttonColor.g,buttonColor.b);
    glVertex3f( leftTop->x, leftTop->y,buttonDepth);
    glVertex3f( rightTop->x, rightTop->y,buttonDepth);
    glVertex3f( rightBottom->x, rightBottom->y,buttonDepth);
    glVertex3f( leftBottom->x, leftBottom->y,buttonDepth);
    glEnd();
}

/*void Button::buttonClickHandler(const function<void ()>& f){
    button_click_handle_function(f);
}*/