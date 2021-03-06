#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "Object.h"

Object::Object(int x, int y, int xm, int ym, Map *mm)
{
	sprite = NULL;
	my_map = mm;
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
	applySurface(box.x, box.y, sprite, screen);
}

Object::~Object()
{
	SDL_FreeSurface(sprite);
}

Sword::Sword(int x, int y, int xm, int ym, Map *mm) : Object::Object(x, y, xm, ym, mm)
{
	atk = rand() % 5 + 2;
}

void Sword::loadSprite()
{
	sprite = loadImage("./resources/sword.bmp");
	if (!sprite)
	{
		std::cout << "Uh-oh";
	}
}
