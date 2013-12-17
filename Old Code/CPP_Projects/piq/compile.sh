#!/bin/bash

BAR="\n\n==========\n\n"
UP="Updating files...\n\n"
MK="Compiling and linking files...\n\n"
DN="\n\nDone!\n\n"

echo -e $BAR$UP

touch *.cpp
touch *.h

echo -e $MK

make

echo -e $DN
