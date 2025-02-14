#include "stdlib.h"
#include "stdio.h"


char PRINTING_BLOCK[] = "█";

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




int main(){


	printf("%s %s \n", BLACK, PRINTING_BLOCK);
	printf("%s %s \n", RED, PRINTING_BLOCK);
	printf("%s %s \n", GREEN, PRINTING_BLOCK);
	printf("%s %s \n", YELLOW, PRINTING_BLOCK);
	printf("%s %s \n", BLUE, PRINTING_BLOCK);
	printf("%s %s \n", MAGENTA, PRINTING_BLOCK);
	printf("%s %s \n", CYAN, PRINTING_BLOCK);
	printf("%s %s \n", WHITE, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_BLACK, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_RED, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_GREEN, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_YELLOW, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_BLUE, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_MAGENTA, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_CYAN, PRINTING_BLOCK);
	printf("%s %s \n", BRIGHT_WHITE, PRINTING_BLOCK);
	

	return EXIT_SUCCESS;
}
