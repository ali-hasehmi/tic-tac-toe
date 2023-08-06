#include <stdio.h>
#include <stdlib.h>
	
#define OR  ||
#define AND &&

	char board[9];
	void board_init();
	void board_print(int curr);
	void board_clear();
	void clear_screen();
	int main(int argc, char *argv[]){

		board_init();

		int index = 0;	
		board_print(index);
		char input;
		while((input=getchar())!='4'){
			if(input == '\033')
			{
				getchar();
				switch(getchar())
				{
					case 'A': //up
						if(index!=0 AND index!=1 AND  index !=2) {
							index -= 3;
						}	
						break;
					case 'B': //down
						  if(index != 6 AND index != 7 AND index != 8){
							  index +=3;
						  }
						  break;
					case 'C': //right
						  if(index != 2 AND index != 5 AND index != 8)
						  {
							  index++;
						  }
						  break;
					case 'D': //left
						  if(index != 0 AND index != 3 AND index != 6){
							  index--;
						  }
						  break;
				}
				board_print(index);
				printf("index = %d \n",index);
			}
		}
		getchar();

	return 0; 
}
void board_init(){

	#ifdef _WIN32
		// if os is windows(either 64 or 32) these lines will be executed
		system("chcp 65001");
	#endif
	
	#ifdef __linux__
		// if os is linux these lines will be executed
		printf("this program is running on linux operating system!\n");
	#endif
	board_clear();
	}
	void board_print(int curr){
		
		clear_screen();
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
						if(index == curr){
							printf("\033[31;107;4m%c\033[0m",board[index++]);
						}
						else{
							printf("%c",board[index++]);
						}	

					}
					else{
						printf(" ");
					}
				}
			}
			printf("\n");
	       	}
	}

	void clear_screen(){
		system("cls || clear");
	}

	void board_clear(){
		for( size_t i = 0 ; i < 9 ; ++i){
			board[i] = 32;
		}
	}
