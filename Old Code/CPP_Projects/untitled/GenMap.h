#ifndef GENMAPH
#define GENMAPH

#define wall 35
#define ground 32
#define door 45
#define sy 33
#define sx 33

class GenMap;

struct Cell
{
	int type;
	bool in_room;
};

typedef Cell MapArray[sy][sx];

class GenMap
{
	private:
	MapArray map;
	
	public:
	GenMap();
	~GenMap();
	void initMap();
	void buildMap();
	void printMap();
	void addRand();
	void addRooms();
	void addDoors(int, int);
	void removeDoubleDoors(); //XXX optimize XXX
	void removeDeadEnds();
	bool deadEndsExist();
	bool toFile();
	
};

#endif //GENMAPH
