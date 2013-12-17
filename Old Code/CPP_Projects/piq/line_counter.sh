#!/bin/bash
# line counter
# counts total number of lines in cpp and h files, excluding blank lines

cat *.cpp *.h | sed '/^\s*$/d' | wc -l

