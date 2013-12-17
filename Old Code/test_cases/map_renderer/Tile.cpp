#include "main.h"
#include "Tile.h"

Tile::Tile(int x, int y, int tile_type)
{
	box.x = x;
	box.y = y;
	
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	
	type = tile_type;
}

void Tile::show()
{
	//if (check_collision(camera, box) == true)
}
