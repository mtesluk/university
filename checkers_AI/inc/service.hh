#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "spot.hh"
#include "board.hh"

/*
	Print on screen choices which version can we play
*/
void show_menu();

/*
	Coordinates plays player vs player
*/
char play_1_vs_1();

/*
	Coordinates plays player vs computer
*/
char play_vs_comp();