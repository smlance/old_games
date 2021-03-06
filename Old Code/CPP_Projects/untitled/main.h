#ifndef MAINH
#define MAINH

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#include <string>
#include <sstream>
#include <fstream>

extern SDL_Surface *screen;

const int SCREEN_WIDTH = 33*16;
const int SCREEN_HEIGHT = 33*16;
const int SCREEN_BPP = 32;

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int TOTAL_TILES = (SCREEN_WIDTH/TILE_WIDTH)*(SCREEN_HEIGHT/TILE_HEIGHT);
const int TILE_SPRITES = 4;

#endif //MAINH
