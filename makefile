#!/bin/zsh

directory=src/

all: ${directory}dsh

${directory}dsh: ${directory}dsh.c
	clang -c ${directory}lane_functions.c ${directory}list_functions.c ${directory}options.c ${directory}command_functions.c
	clang -Wall -Wextra -o dsh ${directory}dsh.c lane_functions.o list_functions.o options.o command_functions.o

dsh_test:
	clang -c ${directory}lane_functions.c ${directory}list_functions.c ${directory}options.c ${directory}command_functions.c
	clang -Wall -Wextra -Werror -o testdsh ${directory}test.c lane_functions.o list_functions.o options.o command_functions.o

clean:
	rm -rf dsh
	rm -rf lane_functions.o
	rm -rf list_functions.o
	rm -rf options.o
	rm -rf command_functions.o

clean_test:
	rm -rf testdsh

