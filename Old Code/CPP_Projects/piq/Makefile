all: piq

piq: main.o game.o display.o timer.o entity.o editor.o
	g++ -std=c++0x main.o game.o display.o timer.o entity.o editor.o -o piq -lSDLmain -lSDL -lSDL_image -lSDL_ttf -W -Wall -ansi -pedantic -g
	
main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp
	
display.o: display.cpp
	g++ -c display.cpp

timer.o: timer.cpp
	g++ -c timer.cpp
	
entity.o: entity.cpp
	g++ -c entity.cpp
	
editor.o: editor.cpp
	g++ -c editor.cpp
	
clean:
	rm -rf *o #piq
