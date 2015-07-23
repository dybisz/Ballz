#ifndef GFX_INCLUDE_MAIN_MENU_H_
#define GFX_INCLUDE_MAIN_MENU_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.h"
#include "error_const.h"
#include "config.h"
#include "button.h"
#include "floating_window.h"
#include <string>

using namespace std;

class MainMenu: public Drawable
{
public:
    Config* config;
    vector<Button*>* buttonVector;
    vector<FloatingWindow*>* floatingWindowVector;
    MainMenu();
    MainMenu(Config* config);
    virtual ~MainMenu();



    int render();
    int handleInput(Config* config, vector<Drawable*> states);
};

#endif