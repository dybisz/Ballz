#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <vector>
#include "drawable.hpp"
#include "config.hpp"
#include "error_const.hpp"

using namespace std;

class MainMenu: public Drawable
{
public:
    MainMenu();
    virtual ~MainMenu();

    int render();
    int handleInput(Config* config, vector<Drawable*> states);
};

#endif