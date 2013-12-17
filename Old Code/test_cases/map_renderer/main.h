#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

class Player;

extern SDL_Surface *screen;
extern SDL_Surface *seconds;
extern SDL_Surface *message;
extern SDL_Surface *background;
extern SDL_Event event;
extern TTF_Font *font;
extern SDL_Color text_color;

const int sy = 4;
const int sx = 5;

const int FRAMES_PER_SECOND = 20;

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 256;
const int SCREEN_BPP = 32;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TOTAL_TILES = sy*sx;
const int TOTAL_SPRITES = 4;

const int TILE_WALL = 0;
const int TILE_GROUND = 1;
const int TILE_DOOR = 2;
const int TILE_NULL = 3;

SDL_Surface *loadImage(std::string filename);
void applySurface(int x, int y, SDL_Surface* source, 
	SDL_Surface* destination);
void handleEvents();
bool init();
void cleanUp();
bool loadSpriteFile(SDL_Surface *sprite, std::string path);

#endif
