#ifndef MAIN_H
#define MAIN_H

	// c++ standard library stuff
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>

	// other important included files (not mine)
//#include "boost/multi_array.hpp"

	// preprocessor directives
#define SCREEN_WIDTH 	320
#define SCREEN_HEIGHT 	240
#define FPS				60

extern bool FULLSCREEN;

	// classes, structs
class Game;
class Display;
class Viewer;
class Font;
class Timer;
class Menu;

class Entity;
class Player;
class Block;
class Area;

class Editor;

	// the files. order is crucial! (moving around "graphics.h" screws it all up)
#include "graphics.h"
#include "game.h"
#include "display.h"
#include "timer.h"
#include "entity.h"
#include "editor.h"

	// the globals
extern Display 		display;
extern SDL_Event 	event;
extern Game 		game;

	// the debugging functions
extern void output(std::string);
extern std::string int_to_str(int);

#endif
