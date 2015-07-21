#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <vector>
#include "drawable.hpp"
#include "error_const.hpp"
#include "config.hpp"
#include "button.hpp"
#include "floating_window.hpp"
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