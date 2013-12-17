#!/bin/bash

g++ *.cpp -o jarl -lSDL -lSDLmain -lSDL_image -g
rm -f *.o

# warning options: -W -Wall -ansi -pedantic -g
