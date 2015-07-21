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
    ball.setView(devCamera.getView());
    ball.setProjection(devCamera.getProjection());
    ball.render();

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