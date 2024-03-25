
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>


#include "CPU_Token.h"

int main(int argc, char **argv)
{
    FILE *fptr ;
    int i = 100 ;
    char myString[100] ;
    // char modified[100] ;
    char *token;
    const char delimiter[2] = " " ;
    // struct CPU_info *info =  (struct CPU_info*) malloc(sizeof(struct CPU_info)) ;
    unsigned long val ;
    unsigned long last_total = 0 ;
    unsigned long total = 0 ;
    clock_t timesnap ;

    while (i > 0)
    {
        last_total = total ;
        total = 0 ;
        fptr = fopen("/proc/stat", "r") ;
        fgets(myString, 100, fptr) ;
        // info_load(myString, info); 
        // for (int i = 0; i < CPU_TOKEN_ARRAY_SIZE; i++)
        //     printf("%ld", info->array[i]) ;
        token = strtok(myString, delimiter) ;
        token = strtok(NULL, delimiter) ;

        while (token != NULL)
        {
            // printf("%s ", token) ;
            val = strtoul(token, NULL, 10) ;
            printf("%ld ", val) ;
            total +=  val ;
            token = strtok(NULL, delimiter) ;
        }
        printf("total= %ld ", total) ;
        printf("diff = %ld ", total- last_total) ;
        
        timesnap = clock() ;
        sleep(1) ;
        timesnap = clock() - timesnap ;
        printf("speed = %ld", timesnap) ;
        printf("\n") ;


        fclose(fptr) ;
        
        i-- ;
    }
    // free(info) ;
    return 0 ;
}