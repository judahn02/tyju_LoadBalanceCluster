
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "tableManage.h"
#include "sharedFunctions.h"

void tmanage_init(int worldSize, int worldRank)
{
    // set up recieving thread
    int killvalue = 1 ;
    pthread_t pid ;
    
    pthread_create(&pid, NULL, setkill, (void *)&killvalue) ;
    // start up collecting PS values
    while(killvalue)
    {
        sleep(1) ;
        printf("tableManage is running\n") ;
    }
    // sleep(3) ;
    

    // // 
    printf("Table is done running\n") ;
    pthread_join(pid, NULL) ;

    // sleep(3) ;
    printf("I am the table manager.\n") ;

    // MPI_Barrier(MPI_COMM_WORLD) ;

    pthread_create(&pid, NULL, thrededBarrier, NULL) ;
    pthread_join(pid, NULL) ;

    return ;    
}

