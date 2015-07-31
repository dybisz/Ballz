#ifndef GFX_INCLUDE_MAIN_H_
#define GFX_INCLUDE_MAIN_H_

#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ball.h"
#include "game.h"
#include "error_const.h"
#include "gl_util.h"
#include "config.h"
#include "main_menu.h"
#include "window_content.h"


/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WINDOW_NAME                     "BALLZ"
#define GL_TARGET_VER_MAJOR             2
#define GL_TARGET_VER_MINOR             1
#define MAIN_MENU                       1
#define GAME                            2
#define GAME_MENU                       3

using namespace std;

/**
 * Handle to the main window of the game, created by SDL.
 */
SDL_Window* gWindow = NULL;

/**
 * Object of the game.
 */
Game* gGame = NULL;

/**
 * Object of main menu.
 */
MainMenu* gMainMenu = NULL;

/**
 * Handle to the OpenGL context.
 */
SDL_GLContext gContext;

/**
 * Holds base game flow information like screen width, screen height etc.
 * Declared not as a pointer because all other globals are initialized after
 * GLEW is triggered and this one is needed before it - during window initialization.
 */
Config gConfig;

/**
 * Holds all available states of the game. Useful when making handle input procedure
 * independent of the main class.
 */
vector<Drawable*> gStates;

/**
 * Points to current states in which the game is.
 */
Drawable* gActive = NULL;

/*
 *  Holds all available states of the game, content of main window, etc.
 */

WindowContent* windowContent = NULL;

/**
 * Main loop of the game. Every event and rendering routine is called here.
 */
int gameLoop();

/**
 * Calls appropriate render() method according to 'gameState' variable.
 */
int renderState();

/**
 * Calls appropriate handleInput() method according to 'gameState' variable;
 */
int handleStateInput();

/**
 * Initializes and checks for error following classes:
 * - MainMenu
 * - Game
 * - GameMenu
 */
int initInstances();

/**
 * Basic initialization of OpenGL environment. Nothing fancy here.
 */
int initGL();

/**
 * Set GLEW to running and handle errors.
 */
int initGLEW();

/**
 * Initialization of SDL.
 */
int initSDL();

/**
 * Creates window choosing target OpenGL version. GL_TARGET_VER_MAJOR and
 * GL_TARGET_VER_MINOR play crucial roles.
 */
int createWindow();

/**
 * Using appropriate SDL calls, GL context is initialized.
 */
int createGLContext();

/**
 * Enable Vsync - whatever it means.
 */
int enableVsync();

/**
 * Function created with hope that during development process, all memory realising
 * routines associated with dynamically created objects (either global or internal)
 * will be handled by this procedure.
 */
int cleanup();

void showFPS(int fps);

double clockToMilliseconds(clock_t ticks);

#endif