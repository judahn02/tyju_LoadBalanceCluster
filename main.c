
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Description:
    This program will demonstrate the application of the 
    functions that are responsiable for calcuating the 
    Priority service value.
*/

#define MAX_LINE_LENGTH 1024 

double getCPUspeed(void) ;

void getIdleRateAndFreeRam(double[2]) ;

int main(int argc, char **argv)
{
    // call for CPU speed in GHz
    double CPUspeed = getCPUspeed() ;
    // printf("%f\n", CPUspeed) ;
    // call for CPU IDLE rate and Ram Idle Size MB
    double idleNfram[2] ;
    


    // calculate the Rv weight 

    //print PS value.

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

void getIdleRateAndFreeRam(double data[2])
{

}