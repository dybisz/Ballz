#include "game.hpp"

const float Game::SCROLL_SPEED = 3.5f;

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
    ball.setCameraPosition(devCamera.getPosition());
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
        /* ----- QUITING GAME ----- */
        if(e.type == SDL_QUIT)
        {
            config->running = false;
        }
        /* ----- MOUSE CLICKED----- */
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            lastClickedX = e.motion.x;
            lastClickedY = e.motion.y;
        }
        /* ----- MOUSE DRAGGED WITH LEFT BUTTON ----- */
        else if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT)
        {
            float deltaX = SCROLL_SPEED * ((float) e.motion.x - (float) lastClickedX) / (float) config->screenWidth;
            float deltaY = SCROLL_SPEED * ((float) e.motion.y - (float) lastClickedY) / (float) config->screenHeight;
            devCamera.updatePosition(deltaX, deltaY);
        }
        /* ----- MOUSE SCROLLED ----- */
        if(e.type == SDL_MOUSEWHEEL)
        {
            devCamera.updateRadius(e.motion.x);
        }
    }
    return SUCCESS;
}
