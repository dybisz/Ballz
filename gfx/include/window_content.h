#ifndef GFX_INCLUDE_WINDOW_CONTENT_H_
#define GFX_INCLUDE_WINDOW_CONTENT_H_

#include "drawable.h"
#include <string>
using namespace std;
class WindowContent {
public:
    WindowContent() {
        gActive = NULL;
    }

    Drawable* gActive;
    Drawable* gMainMenu;
    Drawable* gGame;

    string floatingWindowName = "";

};

#endif