#include <button.h>

//TODO instal https://launchpad.net/ubuntu/+source/freetype


Button::Button(std::string content, float xPos, float yPos, float width, float height,Config* config,WindowContent* windowContent) {
    leftTop = new Point(xPos,yPos);
    leftBottom = new Point(xPos,yPos+height);
    rightTop = new Point(xPos+width,yPos);
    rightBottom = new Point(xPos+width,yPos+height);
    buttonColor = buttonColorNormal;
  //  buttonDepth = BUTTON_DEPTH_NOT_PRESSED;
    this->height=height;
    this->width = width;
    this->content = content;
    this->config = config;
    this->windowContent = windowContent;
    this->fontSize = 10;
    this->fontColor = new Color(1.0f,1.0f,1.0f);

}
Button::Button(std::string content, float xPos, float yPos, float width, float height,Config* config,WindowContent* windowContent, float fontSize, Color* fontColor){
    Button(content,xPos,yPos,width,height,config,windowContent);
    this->fontSize = fontSize;
    this->fontColor = fontColor;
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
        if( ( x > this->leftBottom->x) && ( x < this->rightBottom->x) && ( y <this->leftBottom->y) && ( y > this->leftTop->y ) )
        {
            buttonColor = buttonColorHoover;
        }
            //If not
        else
        {
            buttonColor = buttonColorNormal;
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
            if( ( x > this->leftBottom->x) && ( x < this->rightBottom->x) && ( y < this->leftBottom->y) && ( y > this->leftTop->y) )
            {
                //Set the button sprite
                if(buttonClick != NULL){
                    buttonClick(config,windowContent);
                }
                buttonColor = buttonColorPressed;
                buttonDepth = -5.0f;
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
            if( ( x > this->leftBottom->x) && ( x < this->rightBottom->x) && ( y > this->leftBottom->y) && ( y < this->leftTop->y ) )
            {
                //Set the button sprite
                buttonColor = buttonColorHoover;
            }
        }
    }

}

void Button::draw() {
    glLoadIdentity();                 // Reset the model-view matrix
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);  // Move right and into the screen
    glBegin(GL_POLYGON);
    glColor3f(buttonColor->r,buttonColor->g,buttonColor->b);
    glVertex3f( leftTop->x, leftTop->y,buttonDepth);
    glVertex3f( rightTop->x, rightTop->y,buttonDepth);
    glVertex3f( rightBottom->x, rightBottom->y,buttonDepth);
    glVertex3f( leftBottom->x, leftBottom->y,buttonDepth);
    glEnd();
    glPopMatrix();
    renderText();
}

void Button::setButtonClick(std::function<void(Config* config, WindowContent* windowContent)> func) {
    this->buttonClick = func;
}

/*
 * Function drawing "Content" string on the center of the button
 */
//TODO this funciton needs to be divided to contructing function and drawing function
void Button:: renderText(){
    if(fontSize>50){
        fontSize =50;
    }else if(fontSize<1){
        fontSize=1;
    }
    float scalingFactor = fontSize/80;
    float widthSum=0;
    float heightSum = glutStrokeHeight(GLUT_STROKE_ROMAN);
    for (string::iterator i = content.begin(); i != content.end(); ++i)
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

    for (string::iterator i = content.begin(); i != content.end(); ++i)
    {
        char c = *i;
        glutStrokeCharacter(GLUT_STROKE_ROMAN,c);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Button::setButtonColorHoover(float r, float g, float b) {

    buttonColorHoover = new Color(r,g,b);
}

void Button::setButtonColorNormal(float r, float g, float b) {

    buttonColorNormal = new Color(r,g,b);
}

void Button::setButtonColorPressed(float r, float g, float b) {

    buttonColorPressed = new Color(r,g,b);
}


