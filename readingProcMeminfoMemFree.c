

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH 1024


int main(int argc, char **argv)
{

    char buffer[MAX_LINE_LENGTH] ;

    FILE *fp ;
    fp = open("/proc/meminfo") ;
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to run command\n") ;
        exit(1) ;
    }
    
    fscanf(fp, "%[^\n]", buffer) ;
    printf("%s\n", buffer) ;
    
    
    pclose(fp) ;
    return 0 ;
}