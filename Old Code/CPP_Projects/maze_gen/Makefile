all: mapr

mapr: main.o etc.o Tile.o Map.o GenMap.o Player.o Object.o
	g++ main.o etc.o Tile.o Map.o GenMap.o Player.o Object.o -o mapr -lSDL -lSDL_ttf -lSDL_image -W -Wall -ansi -pedantic -g -ggdb
	
main.o: main.cpp
	g++ -c main.cpp

etc.o: etc.cpp
	g++ -c etc.cpp
	
Tile.o: Tile.cpp
	g++ -c Tile.cpp
	
Map.o: Map.cpp
	g++ -c Map.cpp
	
GenMap.o: GenMap.cpp
	g++ -c GenMap.cpp

Player.o: Player.cpp
	g++ -c Player.cpp
	
Object.o: Object.cpp
	g++ -c Object.cpp
