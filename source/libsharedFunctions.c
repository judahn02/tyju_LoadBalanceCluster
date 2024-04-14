

#include "sharedFunctions.h"
#include <stdio.h>


// setkill is not root dynamic
void *setkill(void *vargp)
{
    int rank ;
    int killTmp ;
    int *killvalue = (int *)vargp ;
    // MPI_Bcast(&killvalue, 1, MPI_INT, 0, MPI_COMM_WORLD) ;
    MPI_Recv(&killTmp, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
    *killvalue = killTmp ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
    printf("rank: %d, killval: %d\n", rank, *killvalue) ;

    pthread_exit(NULL) ;
}
 
void send_kill(int world_size, int rootRank)
{
    int killvalue = 0 ;
    for (int i = 0; i < world_size; i++)
    {
        if (i == rootRank)
            continue;
        MPI_Send(&killvalue, 1, MPI_INT, i,1, MPI_COMM_WORLD) ;
    }
        
        
    // MPI_Bcast(&killvalue, 1, MPI_INT, 0, MPI_COMM_WORLD) ;

    printf("sent kill\n" ) ;
}

void *thrededBarrier(void *vargp)
{
    int rank ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
    MPI_Barrier(MPI_COMM_WORLD) ;
    printf("rank: %d, passed the barrier.\n", rank) ;

    pthread_exit(NULL) ;
}

