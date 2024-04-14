
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "CPU_Idle_Read.h"
#include "RAM_read.h"
#include "CPU_speed_CoreCt.h"

/*
Description:
    This program will demonstrate the application of the 
    functions that are responsiable for calcuating the 
    Priority service value.
*/


int main(int argc, char **argv)
{
    double CPUspeed ;
    int coreCount ;
    int tasks ;
    double priorityServiceValue ;
    // call for CPU speed in GHz
    // double CPUspeed = getCPUspeed(&coreCount) ;               // !!!
    // printf("%f\n", CPUspeed) ;
    // call for CPU IDLE rate and Ram Idle Size MB
    float timeOver = 3 ;// 2 seconds
    float frequency = 0.2 ; // 0.4 seconds refresh
    CPU_Meta meta = CPU_Idle_init(timeOver, frequency) ;
    unsigned long idleDif, totalDif ;
    long double percent ;

    printf("waiting 3 seconds, hold on.\n") ;
    sleep(3) ;

    

    CPUspeed_n_CoreCt(&CPUspeed, &coreCount) ;

    CPU_Idle_Get_Difference(meta, &idleDif, &totalDif) ;   /// !!!

    double freeRam = RAM_freeRam() ;



    percent = (long double) idleDif / totalDif ;
    printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
    printf("the idle percent over a second is: %Lf \n", percent) ;    
    if (freeRam < 500)
        freeRam = 1 ;
    else
        freeRam = freeRam / 500.0 ;

    

    // # of tasks running.
    // coreCount


    //assume that there are 1 tasks running.
    tasks = 1 ;

    //print PS value.
    priorityServiceValue = 
        CPUspeed * percent * freeRam * (coreCount / (1 + tasks)) ;
    printf("\tCPUspeed: %.2f\n", CPUspeed) ;
    printf("\tidle percent: %.2Lf\n", percent) ;
    printf("\tfree RAM value: %.2f\n", freeRam) ;
    printf("\tcore Count: %d\n", coreCount) ;
    printf("\ttasks: %d\n", tasks) ;

    printf("The priority service value is %.4f. \n", priorityServiceValue) ;

    CPU_Idle_Close(meta) ;
    return 0 ;
}
