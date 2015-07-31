#include "main.h"
// TODO(dybisz) unit tests
// TODO(dybisz) better function for error printing
// TODO(dybisz) proper directory structure
// TODO(dybisz) consider try/catch approach rather than ERROR/SUCCCESS
// TODO(dybisz) use asserts
// TODO(dybisz) use namespaces
// TODO(dybisz) legal notice and aouthor line
// TODO(dybisz) do something with GLEW in terms of including order

int main(int argc, char* args[])
{
    glutInit(&argc, args);
    if(ERROR == initSDL())          return EXIT_FAILURE;
    if(ERROR == createWindow())     return EXIT_FAILURE;
    if(ERROR == createGLContext())  return EXIT_FAILURE;
    if(ERROR == initGLEW())         return EXIT_FAILURE;
    if(ERROR == enableVsync())      return EXIT_FAILURE;
    if(ERROR == initInstances())    return EXIT_FAILURE;
    if(ERROR == initGL())           return EXIT_FAILURE;
    if(ERROR == gameLoop())         return EXIT_FAILURE;
    if(ERROR == cleanup())          return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int gameLoop()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glViewport(0, 0, gConfig.screenWidth, gConfig.screenHeight);
    /* ----- SET PROJECTION ----- */
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(90.0f, (GLfloat) config->screenWidth/(GLfloat)config->screenHeight, 1.0f, 1000.0f);
    glOrtho(0.0f, gConfig.screenWidth, gConfig.screenHeight, 0.0f, -5.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW); //set modelview matrix
    glLoadIdentity(); //reset modelview matrix

    float frameCount;
    int currentTime;
    int previousTime = glutGet(GLUT_ELAPSED_TIME);
    int fps;

    SDL_StartTextInput();
    while(gConfig.running)
    {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        showFPS(fps);


        /* ----- KEY HANDLING ----- */
        if(ERROR == handleStateInput()) return ERROR;

        /* ----- RENDERING  -----*/
        if(ERROR == renderState())      return ERROR;

        /* ----- SDL REFRESH ----- */
        SDL_GL_SwapWindow(gWindow);
        //  Increase frame count
        frameCount++;

        //  Get the number of milliseconds since glutInit called
        //  (or first call to glutGet(GLUT ELAPSED TIME)).
        currentTime = glutGet(GLUT_ELAPSED_TIME);

        //  Calculate time passed
        int timeInterval = currentTime - previousTime;

        if (timeInterval > 1000)
        {
            //  calculate the number of frames per second
            fps = frameCount / (timeInterval / 1000.0f);

            //  Set time
            previousTime = currentTime;

            //  Reset frame count
            frameCount = 0;
        }
    }


    SDL_StopTextInput();
    return SUCCESS;
}

int renderState()
{
    if(NULL == windowContent->gActive)
    {
        printf("Uknown game state 2\n");
        return ERROR;
    }
    if(ERROR == windowContent->gActive->render())
    {
        printf("Error during rendering\n");
        return ERROR;
    }
    return SUCCESS;
}

int handleStateInput()
{
    if(NULL == windowContent->gActive) {
        printf("Uknown game state 1\n");
        return ERROR;
    }
    if(ERROR == windowContent->gActive->handleInput(&gConfig, gStates))
    {
        printf("Error during input handling\n");
        return ERROR;
    }
    return SUCCESS;
}

int initInstances()
{
    /* ----- STATE STORAGE ----- */

    if(NULL == (windowContent = new WindowContent))
    {
        printf("Error initializing Game object (WindowContent)\n");
        return ERROR;
    }

    /* ----- GAME ----- */
    if(NULL == (windowContent->gGame = new Game))
    {
        printf("Error initializing Game object\n");
        return ERROR;
    }
    //gStates.push_back(gGame);

    /* ----- MAIN MENU ----- */
    if(NULL == (windowContent->gMainMenu = new MainMenu(&gConfig,windowContent)))
    {
        printf("Error initializing Game object\n");
        return ERROR;
    }
    //gStates.push_back(gMainMenu);

    /* ----- ACTIVE ----- */
    //gActive = gMainMenu;
    windowContent->gActive = windowContent->gMainMenu;
    return SUCCESS;
}

int initGL()
{
    // !!!!!!! TEMPORARY BULLSHIT FOR TESTING
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if(GL_error()) return ERROR;

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if(GL_error()) return ERROR;

    glClearColor(0.f, 0.f, 0.f, 1.f);

    if(GL_error()) return ERROR;

    return SUCCESS;
}

int initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return ERROR;
    }
    else return SUCCESS;
}

int createWindow()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_TARGET_VER_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_TARGET_VER_MINOR);

    gWindow = SDL_CreateWindow(WINDOW_NAME,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               gConfig.screenWidth,
                               gConfig.screenHeight,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS |SDL_WINDOW_FULLSCREEN);


    if(gWindow == NULL)
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return ERROR;
    }
    else return SUCCESS;
}

int createGLContext()
{
    gContext = SDL_GL_CreateContext(gWindow);

    if(gContext == NULL)
    {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return ERROR;
    }

    return SUCCESS;
}

int initGLEW()
{
    glewExperimental= true;
    GLenum err=glewInit();
    if(err!=GLEW_OK)
    {
        //Problem: glewInit failed, something is seriously wrong.
        cout<<"glewInit failed, aborting."<<endl;
        return ERROR;
    }
    return SUCCESS;
}

int enableVsync()
{
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        return ERROR;
    } else return SUCCESS;
}

int cleanup()
{
    delete gGame;
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return SUCCESS;
}

void showFPS(int fps){
    string tmp; // brzydkie rozwiązanie
    sprintf((char*)tmp.c_str(), "%d", fps);
    string str = tmp.c_str();
        float scalingFactor = 50/80;
        float widthSum=0;
        float heightSum = glutStrokeHeight(GLUT_STROKE_ROMAN);
        for (string::iterator i = str.begin(); i != str.end(); ++i)
        {
            char c = *i;
            widthSum += glutStrokeWidth(GLUT_STROKE_ROMAN,c);
        }

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRotatef(180.0,0,1,0);
        glRotatef(180.0, 0,0,1);
        glTranslatef(/*widthSum*scalingFactor*/0,-heightSum/**scalingFactor*/,0);
       // glScalef(scalingFactor,scalingFactor,scalingFactor);
        glColor3f(1.0f, 1.0f, 1.0f); // Green
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(5.0);   // 2.0 gives good results.

        for (string::iterator i = str.begin(); i != str.end(); ++i)
        {
            char c = *i;
            glutStrokeCharacter(GLUT_STROKE_ROMAN,c);
        }
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

}

