#include "floating_window.hpp"

FloatingWindow::FloatingWindow(float width, float height,Config* config) {
    leftTop = new Point(width/2*(-1.0f),height/2*(-1.0f));
    leftBottom = new Point(width/2*(-1.0f),height/2);
    rightTop = new Point(width/2,height/2*(-1.0f));
    rightBottom = new Point(width/2,height/2);

    mouseDown = false;
    mouseCoords = new Point(0.0f,0.0f);

    topBarHeight = 0.1f;

    this->config = config;
}

void FloatingWindow::draw() {



    glBegin(GL_QUADS);
    glColor3f(0.5,0.8,0.8);
    //  printf("*************************");

    glVertex3f( leftBottom->x, leftBottom->y,0.0f);
    glVertex3f( rightBottom->x, rightBottom->y,0.0f);
    glVertex3f( rightBottom->x, rightBottom->y-topBarHeight,0.0f);
    glVertex3f( leftBottom->x, leftBottom->y-topBarHeight,0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.3,0.8);
    //  printf("*************************");
    glVertex3f( leftTop->x, leftTop->y,0.0f);
    glVertex3f( rightTop->x, rightTop->y,0.0f);
    glVertex3f( rightBottom->x, rightBottom->y-topBarHeight,0.0f);
    glVertex3f( leftBottom->x, leftBottom->y-topBarHeight,0.0f);
    glEnd();
}

void FloatingWindow::handle_events(SDL_Event *event) {
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
        SDL_PumpEvents();
        if(mouseDown & SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
            Point* currentCord = new Point(2.0f*x/config->screenWidth-1.0f,2.0f*y/config->screenHeight-1.0f);
            float xDiff = this->mouseCoords->x - currentCord->x;
            float yDiff = this->mouseCoords->y - currentCord->y;

            this->leftTop->x -=xDiff;
            this->leftBottom->x -=xDiff;
            this->rightTop->x -=xDiff;
            this->rightBottom->x -=xDiff;

            this->leftTop->y +=yDiff;
            this->leftBottom->y +=yDiff;
            this->rightTop->y +=yDiff;
            this->rightBottom->y +=yDiff;

            this->mouseCoords->x = currentCord->x;
            this->mouseCoords->y = currentCord->y;
        }

        if(  ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftBottom->y-this->topBarHeight +1.0f)/2* config->screenHeight )) )
        {

           // buttonColor = BUTTON_COLOR_HOOVER;
        }
            //If not
        else
        {
           // this->mouseDown=false;
         //   buttonColor = BUTTON_COLOR_NORMAL;
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
            if( ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftBottom->y-this->topBarHeight +1.0f)/2* config->screenHeight )))
            {
                //Set the button sprite
                printf("mouse down true\n");
                this->mouseDown=true;
                this->mouseCoords->x = 2.0f*x/config->screenWidth-1.0f;
                this->mouseCoords->y = 2.0f*y/config->screenHeight-1.0f;

            }
            else{
                printf("mouse down false\n");
                this->mouseDown=false;
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
            printf("mouse down false\n");
            this->mouseDown=false;

            //If the mouse is over the button
            if(  ( x > (this->leftBottom->x+1.0f)/2* config->screenWidth ) && ( x < (this->rightBottom->x+1.0f)/2* config->screenWidth ) && ( y >(config->screenHeight- (this->leftBottom->y+1.0f)/2* config->screenHeight )) && ( y < (config->screenHeight- (this->leftBottom->y-this->topBarHeight +1.0f)/2* config->screenHeight )))
            {
                //Set the button sprite
               // buttonColor = BUTTON_COLOR_HOOVER;
              //      this->mouseDown=false;
            }
        }
    }
}