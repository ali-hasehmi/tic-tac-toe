#include <stdio.h>
#include <stdlib.h>
	
#define OR  ||
#define AND &&
	char board[9];
	void board_init();
	void board_print();
	int main(int argc, char *argv[]){

		board_init();

		board_print();


		getchar();
	return 0; 
}
void board_init(){

	#ifdef _WIN32
		system("chcp 65001");
	#endif
	
	#ifdef __linux__
		printf("this program is running on linux operating system!\n");
	#endif
	for( size_t i = 0 ; i < 9 ; ++i){
		board[i] = 32;	
	}  

	}
	void board_print(){

		size_t index = 0;
		for( size_t i = 0 ; i < 5 ; ++i){
			for( size_t j = 0 ; j < 17 ; ++j){
				
				if(i == 1 OR i == 3){
					if(j % 6 == 5){
						printf("\u253c");
					}
					else{
						printf("\u2500");
					}
				}	
				else{
					if(j % 6 == 5){
						printf("\u2502");
					}
					else if(j % 6 == 2){
						printf("%c",board[index++]);
					}
					else{
						printf(" ");
					}
				}
			}
		
			printf("\n");
	       	}
	}
