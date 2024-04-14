
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "worker.h"
#include "sharedFunctions.h"

#include "CPU_Idle_Read.h"
#include "RAM_read.h"
#include "CPU_speed_CoreCt.h"

// int killvalue ;

// void *setkill(void *vargp) ;

void worker_init(int worldSize, int worldRank)
{
    int killvalue = 1 ;
    pthread_t pid ;

    double CPUspeed ;
    int coreCount ;
    int tasks ;
    double priorityServiceValue ;
    float timeOver = 3 ;// 2 seconds
    float frequency = 0.2 ; // 0.2 seconds refresh
    CPU_Meta meta = CPU_Idle_init(timeOver, frequency) ;
    unsigned long idleDif, totalDif ;
    long double percent ;
    double freeRam ;
    
    pthread_create(&pid, NULL, setkill,(void *)&killvalue) ;
    printf("waiting 3 for PS value seconds, hold on.\n") ;
    sleep(3) ;
    // start thread for sending PS values
    while(killvalue)
    {
        CPUspeed_n_CoreCt(&CPUspeed, &coreCount) ;

        CPU_Idle_Get_Difference(meta, &idleDif, &totalDif) ;   /// !!!

        freeRam = RAM_freeRam() ;

        percent = (long double) idleDif / totalDif ;
        // printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
        // printf("the idle percent over a second is: %Lf \n", percent) ;    
        if (freeRam < 500)
            freeRam = 1 ;
        else
            freeRam = freeRam / 500.0 ;

        tasks = 1 ;

        priorityServiceValue = 
            CPUspeed * percent * freeRam * (coreCount / (1 + tasks)) ;
        // printf("\tCPUspeed: %.2f\n", CPUspeed) ;
        // printf("\tidle percent: %.2Lf\n", percent) ;
        // printf("\tfree RAM value: %.2f\n", freeRam) ;
        // printf("\tcore Count: %d\n", coreCount) ;
        // printf("\ttasks: %d\n", tasks) ;

        printf("The priority service value of rank %d is %.4f. \n",worldRank, priorityServiceValue) ;
        sleep(1) ;
    }
    

    pthread_join(pid, NULL) ;
    printf("I am the worker\n") ;
    // MPI_Barrier(MPI_COMM_WORLD) ;
    pthread_create(&pid, NULL, thrededBarrier, NULL) ;
    pthread_join(pid, NULL) ;

    CPU_Idle_Close(meta) ;
    return ;
}
