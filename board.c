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

bool set_square(char sign){

	if(board[curr]!=32){
		printf("it's already filled up\r");
		return false;
	}
	board[curr]= sign;
	return true;
}

// return  0 => there is no winner
// return +1 => player won
// reutrn -1 => opponent won
int checkWin(char player,char opponent){
	int sum;	
	// check Rows
	for( int i = 0 ; i < 9 ; i+=3){
		sum = board[i] + board[i+1] + board[i+2];
		if(sum == 3 * player){
			return 1;
		}
		if(sum == 3* opponent){
			return -1;
		}
	}
	// check columns
	for( int i = 0 ; i < 3 ; i++){
		sum = board[i] + board[i+3] + board[i+6];
       		if(sum == 3 * player){
			return 1;
		}			
		if(sum == 3 * opponent){
			return -1;
		}
	}
	// check main diagonal
	sum = board[0] + board[4] + board[8];
	if( sum == 3 * player){
		return 1;
	}
	if( sum == 3 * opponent){
		return -1;
	}
	// check other diagonal
	sum = board[2] + board[4] + board[6];
	if( sum == 3 * player){
		return 1;
	}
	if( sum == 3 * opponent){
		return -1;
	}

	// return 0 indicating there is no winner
	return 0;
}

int checkDraw(){
	for(int i = 0 ; i < 9 ; ++i){
		if(board[i] == 32){
		// there is a empty square
		// return 0 indicates no Draw
			return 0;
		}
	}
	// value 2 will be returned if there was Draw
	return 2;
}

int isGameOver(char _player,char _opp){
	return ( checkWin(_player,_opp) ? checkWin(_player,_opp) : checkDraw() ); 
}
