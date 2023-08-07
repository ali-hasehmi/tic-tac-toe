#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include "board.h"

#ifdef __linux__
#include "input-utils.h"
#endif

#define OR ||
#define AND &&

static char board[9];
static int curr = 0;
static bool my_turn = true;

void clear_screen()
{
	system("cls || clear");
}

void board_init()
{

#ifdef _WIN32
	// if os is windows(either 64 or 32) these lines will be executed
	system("chcp 65001");
#endif

#ifdef __linux__
	// if os is linux these lines will be executed
#endif
	board_clear();
}

void board_print()
{
	clear_screen();
	size_t index = 0;
	for (size_t i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < 17; ++j)
		{

			if (i == 1 OR i == 3)
			{
				if (j % 6 == 5)
				{
					printf("\u253c");
				}
				else
				{
					printf("\u2500");
				}
			}
			else
			{
				if (j % 6 == 5)
				{
					printf("\u2502");
				}
				else if (j % 6 == 2)
				{
					if (index == curr)
					{
						printf("\033[31;107;4m%c\033[0m", board[index++]);
					}
					else
					{
						printf("%c", board[index++]);
					}
				}
				else
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

void board_clear()
{
	for (size_t i = 0; i < 9; ++i)
	{
		board[i] = 32;
	}
}
bool move_focus(){
	unsigned char input;
	int pre_curr = curr;
#ifdef _WIN32
			switch (input = getch())
			{
			case 72: // up
				if (curr != 0 AND curr != 1 AND curr != 2)
				{
					curr -= 3;
				}
				break;
			case 80: // down
				if (curr != 6 AND curr != 7 AND curr != 8)
				{
					curr += 3;
				}
				break;
			case 75: // left
				if (curr != 0 AND curr != 3 AND curr != 6)
				{
					curr--;
				}
				break;
			case 77: // right
				if (curr != 2 AND curr != 5 AND curr != 8)
				{
					curr++;
				}
				break;
			}

#endif


#ifdef __linux__
			getch();
			switch ((input = getch()))
			{
			case 'A': // up
				if (curr != 0 AND curr != 1 AND curr != 2)
				{
					curr -= 3;
				}
				break;
			case 'B': // down
				if (curr != 6 AND curr != 7 AND curr != 8)
				{
					curr += 3;
				}
				break;
			case 'C': // right
				if (curr != 2 AND curr != 5 AND curr != 8)
				{
					curr++;
				}
				break;
			case 'D': // left
				if (curr != 0 AND curr != 3 AND curr != 6)
				{
					curr--;
				}
				break;
			}
#endif
		if(curr == pre_curr){
			return false;
		}
		else{
			return true;
		}
}

bool set_square(){

	if(!my_turn){
		printf("it's not turn, wait for your opponent to make a move\r");
		return false;
	}	
	if(board[curr]!=32){
		printf("it's already filled up\r");
		return false;
	}
	board[curr]='X';
	my_turn = false;
	return true;
}

void board_getinput()
{
	unsigned char input;
	bool need_update = false;
	while ((input = getch()) != '4')
	{
		if (input == 0xE0 OR input == '\033') // check if arrow key pressed
		{
			need_update = move_focus();	
		}
		else if( input == 0x0046 OR input == 0x0066 OR input == 0x000a){ // check if player wants to fill the square
			need_update = set_square();
		}
		if(need_update==true){
		board_print();
		printf("index = %d \n", curr);
		}
	}
}
