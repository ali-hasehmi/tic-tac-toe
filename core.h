#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

#define SINGLE_PLAYER 0
#define MULTI_PLAYER  1

typedef struct player{
	
	char name[20];
	char sign;
	bool turn;
} player_t;

void init_game(const char* _player_name);

void new_game(int _mode,const char* _opp_name);

void swap_turns();
#endif
