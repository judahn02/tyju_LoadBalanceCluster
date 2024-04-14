

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "control.h"
#include "worker.h"
#include "tableManage.h"

// void LoadBalance_Init (int world_size, int world_rank) ;

int main (int argc, char **argv)
{
    // int control = 0 ;
    int provided;
    MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided);
    if(provided < MPI_THREAD_MULTIPLE)
    {
        printf("The threading support level is lesser than that demanded.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    else
    {
        printf("The threading support level corresponds to that demanded.\n");
    }

    int world_size, world_rank ;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank) ;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size) ;

    /*
        Ok, there needs to be at least 3 computers.
        One to be the server, one to be the data table,
        and the rest to be the worker nodes.
    */
    if (world_size < 3)
    {
        printf("There needs to be 3 or more notes to work on.") ;
        MPI_Finalize() ;
        MPI_Abort(MPI_COMM_WORLD, 1) ;
        exit(1) ;
    }
    if (world_rank == 0)
        control_init(world_size, world_rank) ;
    else if (world_rank == 1)
        tmanage_init(world_size, world_rank) ;
    else
        worker_init(world_size, world_rank) ;

    MPI_Finalize() ;
}

// void LoadBalance_Init (int world_size, int world_rank)
// {
//     // maybe a future algorithm to pick which nodes is best to
//     //  be control, Tmanage, and workers. For now: 0 is control,
//     //  1 is Tmanage, and 2+ is the workers.

//     if (world_rank == 0)
//         control_init() ;
//     else if (world_rank == 1)
//         tmanage_init() ;
//     else
//         worker_init() ;
    
//     return ;
// }