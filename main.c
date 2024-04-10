
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "CPU_Idle_Read.h"

/*
Description:
    This program will demonstrate the application of the 
    functions that are responsiable for calcuating the 
    Priority service value.
*/

#define MAX_LINE_LENGTH 1024 

double getCPUspeed(void) ;

int main(int argc, char **argv)
{
    // call for CPU speed in GHz
    double CPUspeed = getCPUspeed() ;
    // printf("%f\n", CPUspeed) ;
    // call for CPU IDLE rate and Ram Idle Size MB
    float timeOver = 3 ;// 2 seconds
    float frequency = 0.2 ; // 0.4 seconds refresh
    CPU_Meta meta = CPU_Idle_init(timeOver, frequency) ;
    unsigned long idleDif, totalDif ;
    long double percent ;

    CPU_Idle_Get_Difference(meta, &idleDif, &totalDif) ;
    percent = (long double) idleDif / totalDif * 100 ;
    printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
    printf("the idle percent over a second is: %Lf%% \n", percent) ;
    // CPU_Idle_Print_Cache(meta) ;


    // calculate the Rv weight 

    //print PS value.


    CPU_Idle_Close(meta) ;
    return 0 ;
}

double getCPUspeed(void)
/*
    Description: 
*/
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
    return total/count2 ;
}
