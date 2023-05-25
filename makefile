#!/bin/zsh

directory=src/

all: ${directory}dsh

${directory}dsh: ${directory}dsh.c
	clang -c ${directory}lane_functions.c ${directory}list_functions.c
	clang -Wall -Wextra -o dsh ${directory}dsh.c lane_functions.o list_functions.o
	
clean:
	rm -rf dsh
	rm -rf lane_functions.o
	rm -rf list_functions.o
