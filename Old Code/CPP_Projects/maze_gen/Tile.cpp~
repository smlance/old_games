#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"

Tile::Tile(int x, int y, int tt, Map *mm)
{
	sprite = NULL;
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	type = tt;
	my_map = mm;
	visibility = 0;
	
	applyVis();
}

void Tile::applyVis()
{
	if (visibility == 0)
	{
		loadInitSprite();
	}
	else if (visibility == 1)
	{
		loadSprite();
	}
	else if (visibility == 2)
	{
		loadObscuredSprite();
	}
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

void Tile::loadObscuredSprite()
{
	if (type == 0)
	{
		sprite = loadImage("./resources/wallobs.png");
	}
	else if (type == 1)
	{
		sprite = loadImage("./resources/groundobs.png");
	}
	else if (type == 2)
	{
		sprite = loadImage("./resources/doorobs.png");
	}
}

void Tile::loadInitSprite()
{
	sprite = loadImage("./resources/fow.bmp");
}

Tile::~Tile()
{
	SDL_FreeSurface(sprite);
}
