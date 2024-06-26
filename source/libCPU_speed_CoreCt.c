
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


#include "CPU_speed_CoreCt.h"


#define MAX_LINE_LENGTH 1024 

void CPUspeed_n_CoreCt(double *speed2, int *coreCt)
{
    FILE *fp ;
    char buffer[MAX_LINE_LENGTH] ;
    int count, count2 = 0 ;
    double speed ;
    double total = 0 ;

    fp = popen("cat /proc/cpuinfo | grep Hz", "r") ;
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n") ;
        exit(1) ; //does C allow throwing of errors?
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char *token = strtok(buffer, " ") ;

        count = 0 ;

        while (token != NULL)
        {
            if (count == 2)
            {
                speed = strtod((const char*)token, NULL) ;
                if (errno == ERANGE)
                {
                    printf("There was an issue with converting the CPU speed.\n");
                    exit(2) ;
                }
                    
                count2++ ;
                total += (speed/1000) ;
            }

            token = strtok(NULL, " ") ;
            count++ ;
        }
    }
    pclose(fp) ;
    *coreCt = count2 ;
    *speed2 = total/count2 ;

    return ;
}