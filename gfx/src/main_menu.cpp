#include "main_menu.hpp"

GLdouble eyeX = 0, eyeY = 0, eyeZ = 0;
GLdouble centerX = 0, centerY = 0, centerZ = 0;
GLdouble upX = 0, upY = 0, upZ = 0;

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(Config* config){
    this->config = config;

    buttonVector = new vector<Button*>();
    floatingWindowVector = new vector<FloatingWindow*>();

    string myString = "test button";
    Button* testButton =  new Button(myString,-0.8f,-0.5f,0.3f,0.1f,this->config);

    buttonVector->push_back(testButton);

    Button* testButton2 =  new Button(myString,-0.8f,-0.2f,0.3f,0.1f,this->config);
    buttonVector->push_back(testButton2);

    FloatingWindow* testFloatingWindow = new FloatingWindow(1.3f,1.3f,this->config);
    floatingWindowVector->push_back(testFloatingWindow);



}

MainMenu::~MainMenu()
{

}

/**
 * Handles rendering of the main menu.
 */
int MainMenu::render()
{
    // !!! TEMPORARY CRAP FOR TESTING
    // !!!
    glMatrixMode(GL_MODELVIEW);

    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    glEnable(GL_BLEND);
   /* gluLookAt(eyeX, eyeY, eyeZ,
              centerX, centerY, centerZ,
              upX, upY, upZ);*/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /*
     * drawing content
     */
    for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
    {
        (*it)->draw();
    }
    for(vector<FloatingWindow*>::iterator it = floatingWindowVector->begin();it != floatingWindowVector->end();it++){
        (*it)->draw();
    }

    return SUCCESS;
}

/**
 * Handles all inputs (keyboard, mouse etc.) of the main menu.
 */
int MainMenu::handleInput(Config* config, vector<Drawable*> states)
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            config->running = false;
        }
        //Handle button events
        for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
        {
            (*it)->handle_events(&e);
        }
        for(vector<FloatingWindow*>::iterator it = floatingWindowVector->begin();it != floatingWindowVector->end();it++){
            (*it)->handle_events(&e);
        }
    }
    return SUCCESS;
}



