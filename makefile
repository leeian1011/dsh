#!/bin/zsh

directory=src/

all: ${directory}dsh

${directory}dsh: ${directory}dsh.c
	clang -c ${directory}save_dir.c
	clang -c ${directory}grab_dir.c
	clang -Wall -Werror -Wextra -o dsh ${directory}dsh.c grab_dir.o save_dir.o
	
clean:
	rm -rf dsh
