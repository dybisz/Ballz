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
#include "window_content.h"
#include <string>
//#include <bits/stl_map.h>
#include <map>


using namespace std;

class MainMenu: public Drawable
{
public:
    Config* config = NULL;
    WindowContent* windowContent = NULL;
    vector<Button*>* buttonVector = NULL;
    map<string,FloatingWindow*>* floatingWindowMap = NULL;
    MainMenu();
    MainMenu(Config* config, WindowContent* windowContent);
    virtual ~MainMenu();

    int render();
    int handleInput(Config* config, vector<Drawable*> states);

    void createServerGUI();

    void findServerGUI();

    void setttingsGUI();
};

#endif