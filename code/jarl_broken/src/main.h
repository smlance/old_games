#ifndef MAIN_H
#define MAIN_H

/*
 *	order matters here. system includes
 *	come first, then classes, then preprocessor
 *	directives, then local headers, then globals.
 */

// standard c headers
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// classes
class Display;
class Camera;
class Game;
class Clock;
class Font;
class Entity;
class Player;
class Map;
class Tile;

// shortened names for std-c and SDL tokens
#define svector			std::vector
#define sstring			std::string
#define scout			std::cout
#define sendl			std::endl
#define Event 			SDL_Event
#define Surface			SDL_Surface
#define Rect			SDL_Rect
#define Key				SDLKey

// gfx/display constants
#define VIDEO_MODE		SCREEN_WIDTH, SCREEN_HEIGHT, 32, \
						SDL_SWSURFACE | SDL_DOUBLEBUF
#define GAME_WIDTH		320
#define GAME_HEIGHT		240
#define TILE_SIDE		16
#define SQ_TXT_SIDE		8
#define TILE_ROWS		GAME_HEIGHT / TILE_SIDE
#define TILE_COLS		GAME_WIDTH / TILE_SIDE
#define MAP_ROWS		TILE_ROWS * 2
#define MAP_COLS		TILE_COLS * 2
#define SCREEN_BUFFER_X TILE_SIDE * 7
#define SCREEN_BUFFER_Y TILE_SIDE * 4
#define SCREEN_WIDTH 	GAME_WIDTH + SCREEN_BUFFER_X
#define SCREEN_HEIGHT 	GAME_HEIGHT + SCREEN_BUFFER_Y
#define FPS				60
#define GFX_PATH		"../gfx/sprite_sheet_16x16.bmp"
#define TXT_PATH		"../gfx/Anikki_font_8x8.bmp"
#define TRANSPARENT		FF00FF

// entity (sub-dungeon) types
#define MOB					0
#define ITEM				1
#define TILE_SOLID			2
#define TILE_NON_SOLID		3

// dungeon types
#define DUNGEON_GRAY		0

// speclecific entity (sub-dungeon) identifiers
#define PLAYER				49
#define RAT					192
#define WALL_GRAY			496
#define STAIRS_DOWN_GRAY	504
#define GROUND_GRAY			508
#define DOOR_CLOSED_GRAY	704
#define DOOR_OPEN_GRAY		705

// moves
#define MOVE_UP			0
#define MOVE_DOWN		1
#define MOVE_LEFT		3
#define MOVE_RIGHT		4

// states
#define STATE_MENU		0
#define STATE_PLAY		1

// jarl headers
#include "gfx.h"
#include "handler.h"
#include "game.h"
#include "disp.h"
#include "clock.h"
#include "ent.h"
#include "map.h"

// global class instances
/*
extern Display 	display;
extern Camera	camera;
extern Game 	game;
extern Handler	handler;
extern Event	event;
extern Clock	fps;
extern Clock	update;*/

#endif // MAIN_H
