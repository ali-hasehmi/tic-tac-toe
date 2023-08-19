#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "core.h"
#include "board.h"
#include "input-utils.h"

#define AND &&
#define OR  ||
#define NOT !

static player_t we; // this client 
static player_t opponent; // opponent

int flip_coin(){
	// create a pseudo-random number between 0 and 1 
	// to determine who plays first
	return (rand()%2);
}

void print_game(){
	clear_screen();
	if(we.turn){
		printf("\033[33;107;1m%s\033[0m",we.name);
		printf(" -vs- %s",opponent.name);
	}else{
		printf("%s",we.name);
		printf(" -vs- \033[33;107;1m%s\033[0m",opponent.name);	
	}
	printf("\n-----------------\n");
	board_print();
}

void init_game(const char* _player_name){
	srand(time(NULL));
	board_init();
	memset(&we,0,sizeof(player_t));	
	memset(&opponent,0,sizeof(player_t));
	strncpy(we.name,_player_name,20);	
}

void swap_turns(){
	bool tmp = we.turn;
	we.turn = opponent.turn;
	opponent.turn = tmp;
}

void waite_for_input(){
	unsigned char input;
	bool need_update;
	int res;
	while (!(res = isGameOver(we.sign,opponent.sign)))
	{
		//printf("res=%d\n",res);
		input = getch();
		need_update = false;
		if (input == 0xE0 OR input == '\033') // check if arrow key pressed
		{
			need_update = move_focus();	
		}
		else if( input == 0x0046 OR input == 0x0066 OR input == 0x000a OR input == 0x000d){ // check if player wants to fill the square
			if(!we.turn){
				printf("it's not your turn!\n");	
			}
			else if((need_update = set_square(we.sign))){
				swap_turns();
			}
		}
		if(need_update==true){
		print_game();
		//printf("index = %d \n", curr);
		}
	}
	
	// check result of isGameOver()
	switch(res){
		case -1:
		printf("You Lost!\n");
			break;

		case 1:
		printf("You Won!\n");		
			break;

		Case 2 :
		printf("Draw!\n");
			break;
		default:
			//do something... 
			//it seems we have a bug...
	}

}
void new_game(int _mode,const char* _opp_name){
	if(_mode == SINGLE_PLAYER ){ // create a new game in single player mode
		we.turn = flip_coin();
		if(we.turn){ // if we have to play first 
			we.sign = 'X';
			opponent.turn = 0;
			opponent.sign = 'O';
		}
		else{ // if opponent have to play first
			we.sign = 'O';
			opponent.turn = 1;
			opponent.sign = 'X';	
		}
		strcpy(opponent.name,"Computer");
		print_game();
		waite_for_input();
	}
}

