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
static int pipes[8][3] = {{0, 1, 2},
						  {3, 4, 5},
						  {6, 7, 8},
						  {0, 3, 6},
						  {1, 4, 7},
						  {2, 5, 8},
						  {0, 4, 8},
						  {2, 4, 6}};

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
bool move_focus()
{
	// printf("board.c 103\n");
	unsigned char input;
	int pre_curr = curr;
#ifdef _WIN32
	switch (input = getch())
	{
	case 72: // up
		if (curr != 0 AND curr != 1 AND curr != 2)
		{
			//printf("board.c up\n");
			curr -= 3;
		}
		break;
	case 80: // down
		if (curr != 6 AND curr != 7 AND curr != 8)
		{
			//printf("board.c down\n");
			curr += 3;
		}
		break;
	case 75: // left
		if (curr != 0 AND curr != 3 AND curr != 6)
		{
			// printf("board.c left\n");
			curr--;
		}
		break;
	case 77: // right
		if (curr != 2 AND curr != 5 AND curr != 8)
		{
			// printf("board.c right\n");
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
	if (curr == pre_curr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool set_square(char sign)
{

	// if square is not empty
	if (board[curr] != 32)
	{
		printf("it's already filled up\r");
		return false;
	}
	// esle
	board[curr] = sign;
	return true;
}

// return  0 => there is no winner
// return +1 => player won
// reutrn -1 => opponent won
int checkWin(char player, char opponent)
{
	int sum;
	// check every pipe for win
	for (int i = 0; i < 8; ++i)
	{
		sum = 0;
		// calculate the sum of the pipe
		for (int j = 0; j < 3; ++j)
		{
			sum += board[pipes[i][j]];
		}
		// check if player won
		if (sum == 3 * player)
		{
			return 1;
		}
		if (sum == 3 * opponent)
		{
			return -1;
		}
	}

	// return 0 indicating there is no winner
	return 0;
}

int checkDraw()
{
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == 32)
		{
			// there is a empty square
			// return 0 indicates no Draw
			return 0;
		}
	}
	// value 2 will be returned if there was Draw
	return 2;
}

int isGameOver(char _player, char _opp)
{
	return (checkWin(_player, _opp) ? checkWin(_player, _opp) : checkDraw());
}

int *close_(char sign)
{
	int sum;
	// accessing every pipe
	for (int i = 0; i < 8; ++i)
	{
		sum = 0;
		// accesting every element of current pipe
		for (int j = 0; j < 3; ++j)
		{
			sum += board[pipes[i][j]];
		}
		// check if there are two same signs with a empty square in the pipe
		if (sum == 2 * sign + 32)
		{
			// return the pipe which is close
			return pipes[i];
		}
	}
	// return NULL indicating there is no close
	return NULL;
}
int *closeWin(char sign)
{
	return close_(sign);
}
int *closeLose(char sign)
{
	return close_(sign);
}
int randMove()
{
	int rand_num;
	do
	{
		rand_num = rand() % 9;
	} while (board[rand_num] != 32);
	return rand_num;
}
int findBestMove(char _player, char _opp)
{
	//========== Critical Condition ============
	int *curr_pipe;
	// check if there is a close win
	if (curr_pipe = closeWin(_player))
	{
		// find the empty square in the pipe
		for (int i = 0; i < 3; ++i)
		{
			// fill the square with player sign
			if (board[curr_pipe[i]] == 32)
			{
				return curr_pipe[i];
			}
		}
	}
	if (curr_pipe = closeLose(_opp))
	{
		// find the empty square in the pipe
		for (int i = 0; i < 3; ++i)
		{
			// fill the square with player sign
			if (board[curr_pipe[i]] == 32)
			{
				return curr_pipe[i];
			}
		}
	}
	//========================================
	// check if center of board is empty
	if (board[4] == 32)
	{
		return 4;
	}

	// return -1 if no best move found
	return -1;
}

int MakeBestMove(char _player, char _opp)
{
	int res;
	if ((res = findBestMove(_player, _opp)) != -1)
	{
		board[res] = _player;
		return 0;
	}
	res = randMove();
	board[res] = _player;
	return 0;
}