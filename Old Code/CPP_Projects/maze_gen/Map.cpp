#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "GenMap.h"

Map::Map()
{
	GenMap this_map;
	if (this_map.toFile())
	{
		loadMap();
	}
}

void Map::loadMap()
{
	int x = 0, y = 0;
	std::ifstream map_file ("./resources/map.txt");
	
	for (int i = 0; i < (SCREEN_HEIGHT/TILE_HEIGHT); i++)
	{
		for (int j = 0; j < (SCREEN_WIDTH/TILE_WIDTH); j++)
		{
			int type = 0;
			map_file >> type;
			tiles[i][j] = new Tile(x, y, type, this);
			x += TILE_WIDTH;
		}
		x = 0;
		y += TILE_HEIGHT;
	}
}

void Map::displayMap()
{
	//applySurface(0, 0, map, screen);
}

void Map::updateDisp(int x, int y)
{
	applySurface(x*TILE_WIDTH, y*TILE_HEIGHT, tiles[y][x]->sprite, screen);
}

bool Map::spaceIsEmpty(int x, int y)
{
	if (tiles[y][x]->type == 0)
	{
		return false;
	};
	return true;
}

Map::~Map()
{
	//SDL_FreeSurface(map);
	//delete tiles;
}
