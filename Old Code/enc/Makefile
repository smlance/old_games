all: enc

enc: main.o misc.o Player.o
	g++ main.o misc.o Player.o -o enc -lncurses

main.o: main.cpp
	g++ -c main.cpp

misc.o: misc.cpp
	g++ -c misc.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

clean:
	rm -rf *o enc
