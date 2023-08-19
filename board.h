#ifndef BOARD_H
#define BOARD_H	

void clear_screen();

void board_init();

void board_print();

void board_clear();

void board_getinput();

bool set_square(char sign);

bool move_focus();

int isGameOver(char _player,char _opp);

#endif

