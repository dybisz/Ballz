#include <floating_window.h>



FloatingWindow::FloatingWindow(float width, float height,Config* config) {
    leftTop = new Point(config->screenWidth/4,config->screenHeight/4);
    leftBottom = new Point(config->screenWidth/4,config->screenHeight/4+height);
    rightTop = new Point(config->screenWidth/4+width,config->screenHeight/4);
    rightBottom = new Point(config->screenWidth/4+width,config->screenHeight/4+height);

    mouseDown = false;
    mouseCoords = new Point(0.0f,0.0f);
    topBarHeight = 30.0f;

    this->config = config;
    buttonVector = new vector<Button*>();
    textBoxVector = new vector<TextBox*>();
}

void FloatingWindow::draw() {




    glBegin(GL_POLYGON);
    glColor3f(0.5,0.3,0.8);
    //  printf("*************************");
    glVertex3f( leftTop->x, leftTop->y+topBarHeight,0.0f);
    glVertex3f( rightTop->x, rightTop->y+topBarHeight,0.0f);
    glVertex3f( rightBottom->x, rightBottom->y,0.0f);
    glVertex3f( leftBottom->x, leftBottom->y,0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5,0.8,0.8);
    //  printf("*************************");

    glVertex3f( leftTop->x, leftTop->y,0.0f);
    glVertex3f( rightTop->x, leftTop->y,0.0f);
    glVertex3f( rightTop->x, leftTop->y+topBarHeight,0.0f);
    glVertex3f( leftTop->x, leftTop->y+topBarHeight,0.0f);
    glEnd();

    //drawing floating window buttons
    for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
    {
        (*it)->draw();
    }
    for(vector<TextBox*>::iterator it = textBoxVector->begin(); it != textBoxVector->end();it++)
    {
        (*it)->draw();
    }
}

void FloatingWindow::addChild(Button* button){
    moveChild(button,this->leftTop->x,this->leftTop->y);
    buttonVector->push_back(button);
}

void FloatingWindow::addChild(TextBox* textBox){
    moveChild(textBox,this->leftTop->x,this->leftTop->y);
    textBoxVector->push_back(textBox);
}

void FloatingWindow::moveChild(Button *button, float x, float y) {
    button->leftTop->x += x;
    button->rightTop->x += x;
    button->rightBottom->x += x;
    button->leftBottom->x += x;
    button->leftTop->y += y;
    button->rightTop->y += y;
    button->rightBottom->y += y;
    button->leftBottom->y += y;
}

void FloatingWindow::moveChild(TextBox *textBox, float x, float y) {
    textBox->leftTop->x += x;
    textBox->rightTop->x += x;
    textBox->rightBottom->x += x;
    textBox->leftBottom->x += x;
    textBox->leftTop->y += y;
    textBox->rightTop->y += y;
    textBox->rightBottom->y += y;
    textBox->leftBottom->y += y;
}

void FloatingWindow::handle_events(SDL_Event *event) {
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if (event->type == SDL_MOUSEMOTION) {
        //Get the mouse offsets
        x = event->motion.x;
        y = event->motion.y;
        // printf("%d:%d\n",x,y);
        //If the mouse is over the button
        SDL_PumpEvents();
        if (mouseDown & SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            Point *currentCord = new Point(x, y);
            float xDiff = this->mouseCoords->x - currentCord->x;
            float yDiff = this->mouseCoords->y - currentCord->y;

            this->leftTop->x -= xDiff;
            this->leftBottom->x -= xDiff;
            this->rightTop->x -= xDiff;
            this->rightBottom->x -= xDiff;

            this->leftTop->y -= yDiff;
            this->leftBottom->y -= yDiff;
            this->rightTop->y -= yDiff;
            this->rightBottom->y -= yDiff;

            for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
            {
                moveChild((*it),-xDiff,-yDiff);
            }
            for(vector<TextBox*>::iterator it = textBoxVector->begin(); it != textBoxVector->end();it++)
            {
                moveChild((*it),-xDiff,-yDiff);
            }

            this->mouseCoords->x = currentCord->x;
            this->mouseCoords->y = currentCord->y;
        }

        if ((x > this->leftBottom->x) && (x < this->rightBottom->x) && (y < this->leftTop->y) &&
                                                                       (y > this->leftTop->y + this->topBarHeight)) {

            // buttonColor = BUTTON_COLOR_HOOVER;
        }
            //If not
        else {
            // this->mouseDown=false;
            //   buttonColor = BUTTON_COLOR_NORMAL;
        }
    }
    //If a mouse button was pressed
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        //If the left mouse button was pressed
        if (event->button.button == SDL_BUTTON_LEFT) {
            //Get the mouse offsets
            x = event->button.x;
            y = event->button.y;

            //If the mouse is over the button
            if ((x > this->leftBottom->x) && (x < this->rightBottom->x) && (y > this->leftTop->y) &&
                                                                           (y < this->leftTop->y +
                                                                                this->topBarHeight)) {
                //Set the button sprite
                printf("mouse down true\n");
                this->mouseDown = true;
                this->mouseCoords->x = x;
                this->mouseCoords->y = y;

            }
            else {
                printf("mouse down false\n");
                this->mouseDown = false;
            }
        }
    }
    //If a mouse button was released
    if (event->type == SDL_MOUSEBUTTONUP) {
        //If the left mouse button was released
        if (event->button.button == SDL_BUTTON_LEFT) {
            //Get the mouse offsets
            x = event->button.x;
            y = event->button.y;
            printf("mouse down false\n");
            this->mouseDown = false;

            //If the mouse is over the button
            if ((x > (this->leftBottom->x + 1.0f) / 2 * config->screenWidth) &&
                (x < (this->rightBottom->x + 1.0f) / 2 * config->screenWidth) &&
                (y > (config->screenHeight - (this->leftBottom->y + 1.0f) / 2 * config->screenHeight)) && (y <
                                                                                                           (config->screenHeight -
                                                                                                            (this->leftBottom->y -
                                                                                                             this->topBarHeight +
                                                                                                             1.0f) / 2 *
                                                                                                            config->screenHeight))) {
                //Set the button sprite
                // buttonColor = BUTTON_COLOR_HOOVER;
                //      this->mouseDown=false;
            }
        }
    }
    //Handle button events
    for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
    {
        (*it)->handle_events(event);
    }
    for(vector<TextBox*>::iterator it = textBoxVector->begin(); it != textBoxVector->end();it++)
    {
        (*it)->handle_events(event);
    }
}
