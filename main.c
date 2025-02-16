#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



char FULL_BLOCK[] = "██";
char THREE_QUART_BLOCK[] = "▓▓";
char HALF_BLOCK[] = "▒▒";
char QUART_BLOCK[] = "░░";


char BLACK[] = "\033[0;30m";
char RED[] = "\033[0;31m";
char GREEN[] = "\033[0;32m";
char YELLOW[] = "\033[0;33m";
char BLUE[] = "\033[0;34m";
char MAGENTA[] = "\033[0;35m";
char CYAN[] = "\033[0;36m";
char WHITE[] = "\033[0;37m";
char BRIGHT_BLACK[] = "\033[0;90m";
char BRIGHT_RED[] = "\033[0;91m";
char BRIGHT_GREEN[] = "\033[0;92m";
char BRIGHT_YELLOW[] = "\033[0;93m";
char BRIGHT_BLUE[] = "\033[0;94m";
char BRIGHT_MAGENTA[] = "\033[0;95m";
char BRIGHT_CYAN[] = "\033[0;96m";
char BRIGHT_WHITE[] = "\033[0;97m";


struct struct_pixel_s {
	int layer[50];
} pixel;



int main(){
 
	while (1) 
	{
		system("clear");
		printf("%s %s%s%s%s\n", BLACK, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", RED, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", GREEN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", YELLOW, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BLUE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", MAGENTA, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", CYAN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", WHITE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_BLACK, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_RED, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_GREEN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_YELLOW, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_MAGENTA, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_CYAN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		printf("%s %s%s%s%s\n", BRIGHT_WHITE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
		
		fflush(stdout);
		sleep(1);
	}
	return EXIT_SUCCESS;
}
