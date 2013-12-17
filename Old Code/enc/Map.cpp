#include "Map.h"

Map::Map(int x, int y)
{
	world_x = x;
	world_y = y;
	size_x = MAP_SIZE_X;
	size_y = MAP_SIZE_Y; /*necessary?
	can't we just use map_x and map_y instead
	of making new vars?*/
	setMapData();
	//printMap();
	//setObjData();
}

Map::setMapData()
{
	
}

Map::~Map()
{
	delete &size_x, &size_y, &world_x, &world_y, data_map, //data_obj;
}
