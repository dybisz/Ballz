#include "game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

/**
 * Core rendering function for the game.
 */
int Game::render()
{
    // !!! TEMPORARY CRAP FOR TESTING
    // !!!

    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //Render quad
    glBegin(GL_QUADS);
    glVertex2f( -0.5f, -0.5f );
    glVertex2f( 0.5f, -0.5f );
    glVertex2f( 0.5f, 0.5f );
    glVertex2f( -0.5f, 0.5f );
    glEnd();

    return SUCCESS;
}

/**
 * Handling inputs across all devices (mouse, keyboard etc) during
 * the game's flow.
 */
int Game::handleInput(Config* config, vector<Drawable*> states)
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            config->running = false;
        }
    }
    return SUCCESS;
}