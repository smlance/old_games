#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "Player.h"

Player::Player()
{
	sprite = loadImage("./resources/player.bmp");
	if (!sprite)
	{
		std::cout << "Unable to load image";
	}
	map_curr = new Map;
	pos_x = 0;
	pos_y = 0;
	old_x = 0;
	old_y = 0;
	dir = 0;
	FOV_radius = 5;
	bool has_pos = false;
	
	while (!has_pos)
	{
		pos_x = rand() % (SCREEN_WIDTH/TILE_WIDTH);
		pos_y = rand() % (SCREEN_HEIGHT/TILE_WIDTH);
		
		if ((map_curr->tiles[pos_y][pos_x]->type) == 1)
		{
			pos_x *= TILE_WIDTH;
			pos_y *= TILE_HEIGHT;
			old_x = pos_x;
			old_y = pos_y;
			has_pos = true;
		}
	}
	
	display();
}

void Player::genFOV(int disp)
{
	/*incrementing by 5 prevents slowdown :)*/
	float x, y;
	int i;
	for (i = 0; i < 360; i+=5)
	{
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);
		if (!disp)
		{
			dispObsFOV(x, y);
		}
		else
		{
			dispFOV(x, y);
		}
	}
}

void Player::dispFOV(float x, float y)
{
	int i;
	float ox, oy;
	ox = (float)(pos_x/TILE_WIDTH)+0.5f;
	oy = (float)(pos_y/TILE_HEIGHT)+0.5f;
	
	for (i = 0; i < FOV_radius; i++)
	{
		map_curr->tiles[(int)oy][(int)ox]->visibility = 1;
		map_curr->tiles[(int)oy][(int)ox]->applyVis();
		
		if (map_curr->tiles[(int)oy][(int)ox]->type == 0)
			return;
		ox+=x;
		oy+=y;
	}
	
}

void Player::dispObsFOV(float x, float y)
{
	int i;
	float ox, oy;
	ox = (float)(old_x/TILE_WIDTH)+0.5f;
	oy = (float)(old_y/TILE_HEIGHT)+0.5f;
	
	for (i = 0; i < FOV_radius; i++)
	{
		map_curr->tiles[(int)oy][(int)ox]->visibility = 2;
		map_curr->tiles[(int)oy][(int)ox]->applyVis();
		
		if (map_curr->tiles[(int)oy][(int)ox]->type == 0)
			return;
		ox+=x;
		oy+=y;
	}
}

void Player::handleInput(SDL_Event &event)
{
	old_x = pos_x;
	old_y = pos_y;
	
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
				if (map_curr->spaceIsEmpty(pos_x/TILE_WIDTH, 
					(pos_y-16)/TILE_HEIGHT))
				{
					map_curr->updateDisp(pos_x/TILE_WIDTH, 
						pos_y/TILE_HEIGHT);
					pos_y -= 16;
				};
				break;
            case SDLK_DOWN: 
            	if (map_curr->spaceIsEmpty(pos_x/TILE_WIDTH, 
					(pos_y+16)/TILE_HEIGHT))
				{
					map_curr->updateDisp(pos_x/TILE_WIDTH, 
						pos_y/TILE_HEIGHT);
					pos_y += 16;
				}
				break;
            case SDLK_LEFT: 
            	if (map_curr->spaceIsEmpty((pos_x-16)/TILE_WIDTH, 
					(pos_y)/TILE_HEIGHT))
				{
					map_curr->updateDisp(pos_x/TILE_WIDTH, 
						pos_y/TILE_HEIGHT);
					pos_x -= 16;
				};
				break;
            case SDLK_RIGHT: 
            	if (map_curr->spaceIsEmpty((pos_x+16)/TILE_WIDTH, 
					(pos_y)/TILE_HEIGHT))
				{
					map_curr->updateDisp(pos_x/TILE_WIDTH, 
						pos_y/TILE_HEIGHT);
					pos_x += 16;
				};
		}
	}
	display();
}

void Player::display()
{
	enum {OLD, NEW};
	
	genFOV(OLD);
	genFOV(NEW);
	applySurface(pos_x, pos_y, sprite, screen);
}

Player::~Player()
{
	//delete map_curr;
	SDL_FreeSurface(sprite);
}
