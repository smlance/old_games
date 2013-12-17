#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "Object.h"
#include "GenMap.h"

Tile::Tile(int x, int y, int tt, Map *mm)
{
	rand_for_ground = rand() % 100; //eww
	sprite = NULL;
	item_list = NULL;
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	type = tt;
	my_map = mm;
	visibility = 0;
	
	applyVis();
}

void Tile::applyShadow()
{
	SDL_Surface *shadow;
	shadow = loadTransparentImage("./resources/black.png");
	
	//SDL_DisplayFormatAlpha(shadow);
	applySurface(box.x, box.y, shadow, screen, NULL);
	SDL_FreeSurface(shadow);
}

void Tile::applyVis()
{
	/*you don't need to load the sprites this many times...?
	also, how do we make initially randomized sprites permanent?*/
	if (visibility == 0)
	{
		loadInitSprite();
		applyToMap();
	}
	else if (visibility == 1)
	{
		loadSprite();
		applyToMap();
	}
	else if (visibility == 2)
	{
		applyToMap();
		applyShadow();
	}
}

void Tile::applyToMap()
{
	//applySurface(box.x, box.y, sprite, my_map->map/*, the tile clipping*/);
	applySurface(box.x, box.y, sprite, screen);
	if (item_list && visibility == 1)
	{
		item_list->item->applyToMap();
		//std::cout << "Item displayed..." << std::endl;
	}
}

void Tile::loadSprite()
{
	
	if (type == 0)
	{
		sprite = loadImage("./resources/wall.png");
	}
	if (sprite == NULL)
	{
		std::abort();
	}
	else if (type == 1)
	{
		if (rand_for_ground < 69)
		{
			sprite = loadImage("./resources/ground.png");
		}
		else
		{
			if (rand_for_ground % 2) //hideous
			{
			sprite = loadImage("./resources/ground1.png");
			}
			else
			{
			sprite = loadImage("./resources/ground2.png");
			}
		}
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
