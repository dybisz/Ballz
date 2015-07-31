

#include "text_box.h"


TextBox::TextBox(float xPos, float yPos, float width, float height, Config *config,
                 WindowContent *windowConent) {

    leftTop = new Point(xPos,yPos);
    leftBottom = new Point(xPos,yPos+height);
    rightTop = new Point(xPos+width,yPos);
    rightBottom = new Point(xPos+width,yPos+height);
    textBoxColor = textBoxColorNormal;
    this->height=height;
    this->width = width;
    this->text = "";
    this->config = config;
    this->windowContent = windowContent;
    this->fontSize = 10;
    this->fontColor = new Color(1.0,1.0,1.0);

}

void TextBox::draw() {
    glLoadIdentity();                 // Reset the model-view matrix
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);  // Move right and into the screen
    glBegin(GL_POLYGON);
    glColor4f( textBoxColor->r,textBoxColor->g,textBoxColor->b,opacity);
    glVertex3f( leftTop->x, leftTop->y,0.0);
    glVertex3f( rightTop->x, rightTop->y,0.0);
    glVertex3f( rightBottom->x, rightBottom->y,0.0);
    glVertex3f( leftBottom->x, leftBottom->y,0.0);
    glEnd();
    glPopMatrix();
    renderText();
}

/*
 * Function drawing "Content" string on the center of the button
 */
//TODO this funciton needs to be divided to contructing function and drawing function
void TextBox:: renderText(){
    if(fontSize>50){
        fontSize =50;
    }else if(fontSize<1){
        fontSize=1;
    }
    float scalingFactor = fontSize/80;
    float widthSum=0;
    float heightSum = glutStrokeHeight(GLUT_STROKE_ROMAN);
    for (string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        widthSum += glutStrokeWidth(GLUT_STROKE_ROMAN,c);
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(180.0,0,1,0);
    glRotatef(180.0, 0,0,1);
    glTranslatef(leftBottom->x+this->width/2-widthSum*scalingFactor/2,- this->leftBottom->y+height/2 - heightSum*scalingFactor/4,0);
    glScalef(scalingFactor,scalingFactor,scalingFactor);
    glColor3f(fontColor->r, fontColor->g, fontColor->b); // Green
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0);   // 2.0 gives good results.

    for (string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutStrokeCharacter(GLUT_STROKE_ROMAN,c);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void TextBox::handle_events(SDL_Event* event) {
    //The mouse offsets
    int x = 0, y = 0;
    if(isEditingEnabled) {
        //If the mouse moved
        if (event->type == SDL_MOUSEMOTION) {
            //Get the mouse offsets
            x = event->motion.x;
            y = event->motion.y;
            // printf("%d:%d\n",x,y);
            //If the mouse is over the button
            if ((x > this->leftBottom->x) && (x < this->rightBottom->x) && (y < this->leftBottom->y) &&
                                                                           (y > this->leftTop->y)) {

                textBoxColor = textBoxColorHoover;
            }
                //If not
            else {
                if (isInputActive)
                    textBoxColor = textBoxColorPressed;
                else
                    textBoxColor = textBoxColorNormal;
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
                if ((x > this->leftBottom->x) && (x < this->rightBottom->x) && (y < this->leftBottom->y) &&
                                                                               (y > this->leftTop->y)) {
                    //Set the button sprite
                    /* if(buttonClick != NULL){
                    buttonClick(config,windowContent);
                }*/
                    textBoxColor = textBoxColorPressed;
                    isInputActive = true;
                    SDL_StartTextInput();
                    // button_click_handle_function();
                }
                else {
                    textBoxColor = textBoxColorNormal;
                    isInputActive = false;
                    SDL_StopTextInput();
                }
            }
        }
        if (event->type == SDL_TEXTINPUT) {
            text += event->text.text;
        }
        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_BACKSPACE && isInputActive == true) {
                text = text.substr(0, text.size() - 1);
            }
        }




        //If a mouse button was released
        /* if( event->type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event->button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event->button.x;
            y = event->button.y;

            //If the mouse is over the button
            if( ( x > this->leftBottom->x) && ( x < this->rightBottom->x) && ( y > this->leftBottom->y) && ( y < this->leftTop->y ) )
            {
                //Set the button sprite
                textBoxColor = textBoxColorHoover;
            }
        }
    }*/
    }
}