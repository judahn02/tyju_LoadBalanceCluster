#include <stdio.h>

/*
    THis program is not being continued because it leads to 
    the quivalent of a dead end. Please readNotes.
*/

#define MAX_LINE_LENGTH 1024

void loadBufferFromPSCommand(char*) ;

int main(int argc, char **argv)
{
    char buffer[MAX_LINE_LENGTH] ;




}

void loadBufferFromProcStat(char *buffer)
/*
    This program pulls a modified command call
    of PS to see what are the top CPU utilizing
    processes currently being used.
*/
{
    FILE *fp ;

    // Opens pipe
    fp = popen("cat /proc/stat", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run top command\n");
        exit(1);
    }

    // loads buffer until it hits the first line.
    fscanf(fp, "%[^\n]", buffer) ;

    // Use for testing
    // printf("%s\n", buffer) ;
    pclose(fp);
}