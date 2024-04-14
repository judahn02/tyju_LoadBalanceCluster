#ifndef __SHAREDFUNCTIONS_H__
#define __SHAREDFUNCTIONS_H__
/*
    Remember, these functions and values are the same on all programs,
    there will be an instance for each program to use differently. 
*/

#include <mpi.h>
#include <pthread.h>

// int killvalue ;

void *setkill(void *vargp) ;

void send_kill(int world_size, int rootRank) ;

void *thrededBarrier(void *vargp) ;



#endif