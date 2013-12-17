#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "Object.h"

Object::Object(int x, int y, int xm, int ym, Map *mm, Tile* mt)
{
	sprite = NULL;
	my_map = mm;
	my_tile = mt;
	pos_x = 0;
	pos_y = 0; /*can be removed*/
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	map_x = xm;
	map_y = ym;
	
	loadSprite();
	applyToMap();
}

void Object::loadSprite()
{
	sprite = NULL;
}

void Object::applyToMap()
{
	if (my_tile->visibility == 1)
	{
		applySurface(box.x, box.y, sprite, screen);
	}
	/*else if (my_tile->visibility == 2)
	{
		my_tile->applyToMap();
	}*/
}

Object::~Object()
{
	SDL_FreeSurface(sprite);
	delete list;
}

Sword::Sword(int x, int y, int xm, int ym, Map *mm, Tile *mt) : Object(x, y, xm, ym, mm, mt)
{
	atk = rand() % 5 + 2;
	loadSprite();
	//applyToMap();
}

void Sword::loadSprite()
{
	sprite = loadImage("sword.bmp");
}

Potion::Potion(int x, int y, int xm, int ym, Map *mm, Tile *mt) : Object(x, y, xm, ym, mm, mt)
{
	heal_amt = rand() % 5 + 1;
	loadSprite();
	//applyToMap();
}

void Potion::loadSprite()
{
	sprite = loadImage("./resources/potion.bmp");
}
