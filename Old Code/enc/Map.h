#ifndef MAP_H
#define MAP_H

/*Possibility for map gen algorithm:
	Pick two initial starting positions and get random values
	for direction and length. Draw lines. Continue doing this until
	two lines overlap each other. If there is an overlap, draw a room.
	At the end, check if any lines have gone off the map. (?)*/
class Map
{
	private:
	int size_x, size_y, world_x, world_y;
	norm_array data_map, data_obj;
	
	public:
	Map(int, int);
	~Map();
	void printCell();
	/* printCell: translates map data to printable char and prints*/
	void printMap();
	/* printMap: prints map*/
	void updateMap(int, int, int);
	/* updateMap: takes x-y coords of player and his last direction.
	blits the cell he passed over to the screen.*/
	bool isSpaceTaken(int, int);
	/* isSpaceTaken: is this x-y position not a free space? */
	void setMapData();
	/* setMapData: looks at this map's world-map position and
	copies data from there to here */
	void setObjData();
	/* setObjData: same thing as setMapData but for object map */
	void readObjMap();
	/* readObjMap: goes through obj map data and creates objects */
	void createObjs();
	/* dynamic object creation */
	
	friend class Object;
	friend class Player;
};

#endif
