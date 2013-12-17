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
	dir = 0;
	bool has_pos = false;
	
	while (!has_pos)
	{
		pos_x = rand() % (SCREEN_WIDTH/TILE_WIDTH);
		pos_y = rand() % (SCREEN_HEIGHT/TILE_WIDTH);
		
		if ((map_curr->tiles[pos_y][pos_x]->type) == 1)
		{
			pos_x *= TILE_WIDTH;
			pos_y *= TILE_HEIGHT;
			has_pos = true;
		}
	}
	
	display();
}

void Player::handleInput(SDL_Event &event)
{
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
	applySurface(pos_x, pos_y, sprite, screen);
}

Player::~Player()
{
	//delete map_curr;
	SDL_FreeSurface(sprite);
}
