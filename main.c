#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#define OR ||
#define AND &&


int main(int argc, char *argv[])
{

	board_init();

	board_print();

	board_getinput();


	return 0;
}

