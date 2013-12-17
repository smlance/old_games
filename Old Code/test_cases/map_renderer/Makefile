all: map_rend

map_rend: main.o Player.o Timer.o
	g++ main.o Player.o Timer.o -o map_rend -g -lSDL -lSDL_ttf -W -Wall -ansi -pedantic
	
main.o: main.cpp
	g++ -c main.cpp

Player.o: Player.cpp
	g++ -c Player.cpp
	
Timer.o: Timer.cpp
	g++ -c Timer.cpp
