#include "CPU_Token.h"

void info_load(char *string, struct CPU_info *C_info)
/*
    Input: a preformatted string of "cpu #1 #2 #3 #4 #5 #6 #7 #8 #9 #10"
            and an empty integer list of 10 integers.
    Output: a modified empty integer list of 10 integers.
    
*/
{
    char *token ;
    char *delimiter = " " ;
    int count = 0 ;

    token = strtok(string, delimiter) ; //skip 'cpu'
    token = strtok(NULL, delimiter) ; 
    
    while(token != NULL)
    {
        C_info->array[count++] = strtoul(token, NULL, 10) ;
        token = strtok(NULL, delimiter) ;
    }
}