#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
FILE* tfile;

void exitProgram(int sig) {
	fclose(tfile);
	exit(0);
}
int main(void) {
	signal(SIGINT, exitProgram);
	tfile = fopen("e.txt", "w");
    while (true) {
		fputs("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee", tfile);
	}
}
 