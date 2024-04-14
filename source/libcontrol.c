
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "control.h"
#include "sharedFunctions.h"



void control_init(int worldSize, int worldRank)
//  This is node 0
{
    // Initializing
    pthread_t pid ;
    printf("sleeping for 8 seconds.\n") ;
    sleep(8) ;
    send_kill(worldSize, worldRank) ;





    // sent the kill command.
    printf("I am the control.\n") ;

    // MPI_Barrier(MPI_COMM_WORLD) ;

    pthread_create(&pid, NULL, thrededBarrier, NULL) ;
    pthread_join(pid, NULL) ;
    return ;

}

