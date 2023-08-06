#include <stdio.h>
#include <stdlib.h>
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

void board_getinput()
{
	unsigned char input;
	while ((input = getch()) != '4')
	{

#ifdef _WIN32

		if (input == 0xE0) // to check scroll key interrupt
		{

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
			};
		}

#endif

#ifdef __linux__
		if (input == '\033')
		{
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
		}
#endif
		board_print();
		printf("index = %d \n", curr);
	}
}
