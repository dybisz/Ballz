#ifndef GFX_INCLUDE_CONFIG_HPP_
#define GFX_INCLUDE_CONFIG_HPP_

#include "drawable.h"

class Config {
public:
    Config() {
        screenWidth = 800;
        screenHeight = 600;
        running = true;
    }

    //  Width of the game screen. Declared neither as const nor with #define,
    //  because during game flow, user can change e.g. resolution.
    int screenWidth;
    /*
     * Height of the game screen. Declared neither as const nor with #define,
     * because during game flow, user can change e.g. resolution.
     */
    int screenHeight;
    /**
     * Variable controls if there is still a need for keep
     * running the game. E.g user decided to close window, then
     * running will be set to false;
     */
    bool running;

};

#endif