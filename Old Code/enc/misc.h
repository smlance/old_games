#ifndef MISC_H
#define MISC_H

#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*XXX XXX XXX IMPORTANT XXX XXX XXX
make sure circular definitions/includes
DO NOT EXIST! How can the header files
be listed so that each file doesn't
have to include them, but so we can
have them in a specific order? or should
we include separately for each file?*/
#include "Player.h"
/*XXX Player.h includes misc.h... How to
fix?*/

#define MAP_SIZE_Y 13
#define MAP_SIZE_X 13
#define W_MAP_SIZE_Y 5
#define W_MAP_SIZE_X 5

typedef int norm_array[MAP_SIZE_Y][MAP_SIZE_X];

extern norm_array world_map[W_MAP_SIZE_Y][W_MAP_SIZE_X];

//extern Player player; necessary?
/*class Player;
class Map;
class Object;
class StatusBar;*/

void init();
void loop();

#endif
