

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CPU_Idle_Read.h"

int main(int argc, char **argv)
{

    float timeOver = 3 ;// 2 seconds
    float frequency = 0.2 ; // 0.4 seconds refresh
    CPU_Meta meta = CPU_Idle_init(timeOver, frequency) ;

    int loop = 1 ;
    int userInput ;

    unsigned long idleDif, totalDif ;
    long double percent ;


    while(loop)
    {
        printf("Please enter 1 or 0: 1 to get current idle/total values, 0 to exit.: ") ;
        if (scanf("%d", &userInput) == 1) {
            if (userInput == 1)
            {
                CPU_Idle_Get_Difference(meta, &idleDif, &totalDif) ;
                percent = (long double) idleDif / totalDif * 100 ;
                printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
                printf("the idle percent over a second is: %Lf%% \n", percent) ;
            }
            else if (userInput == 0)
            {
                CPU_Idle_Print_Cache(meta) ;
                break ;
            }
            else
                printf("That was an interger but not 1 or 0 :(.\n") ;
                
        } else {
            printf("Invalid input. Please enter an integer.\n");
        }
    }

    CPU_Idle_Close(meta) ;
    return 0 ;
}