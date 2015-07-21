#include "main.hpp"

//TODO unit tests
//TODO better function for error printing
//TODO proper directory structure
//TODO consider try/catch approach rather than ERROR/SUCCCESS

int main(int argc, char* args[])
{
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
    SDL_StartTextInput();
    while(gConfig.running)
    {
        /* ----- KEY HANDLING ----- */
        if(ERROR == handleStateInput()) return ERROR;

        /* ----- RENDERING  -----*/
        if(ERROR == renderState())      return ERROR;

        /* ----- SDL REFRESH ----- */
        SDL_GL_SwapWindow(gWindow);
    }

    SDL_StopTextInput();
    return SUCCESS;
}

int renderState()
{
    if(NULL == gActive)
    {
        printf("Uknown game state\n");
        return ERROR;
    }
    if(ERROR == gActive->render())
    {
        printf("Error during rendering\n");
        return ERROR;
    }
    return SUCCESS;
}

int handleStateInput()
{
    if(NULL == gActive) {
        printf("Uknown game state\n");
        return ERROR;
    }
    if(ERROR == gActive->handleInput(&gConfig, gStates))
    {
        printf("Error during input handling\n");
        return ERROR;
    }
    return SUCCESS;
}

int initInstances()
{
    /* ----- GAME ----- */
    if(NULL == (gGame = new Game))
    {
        printf("Error initializing Game object\n");
        return ERROR;
    }
    gStates.push_back(gGame);

    /* ----- MAIN MENU ----- */
    if(NULL == (gMainMenu = new MainMenu))
    {
        printf("Error initializing Game object\n");
        return ERROR;
    }
    gStates.push_back(gMainMenu);

    /* ----- ACTIVE ----- */
    gActive = gGame;

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
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

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
