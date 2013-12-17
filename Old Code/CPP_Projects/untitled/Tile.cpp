#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"

Tile::Tile(int x, int y, int tt, Map *mm)
{
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	type = tt;
	my_map = mm;
	
	loadSprite();
	applyToMap();
}

void Tile::applyToMap()
{
	//applySurface(box.x, box.y, sprite, my_map->map/*, the tile clipping*/);
	applySurface(box.x, box.y, sprite, screen);
}

void Tile::loadSprite()
{
	if (type == 0)
	{
		sprite = loadImage("./resources/wall.png");
	}
	else if (type == 1)
	{
		sprite = loadImage("./resources/ground.png");
	}
	else if (type == 2)
	{
		sprite = loadImage("./resources/door.png");
	}
}

Tile::~Tile()
{
	SDL_FreeSurface(sprite);
}
