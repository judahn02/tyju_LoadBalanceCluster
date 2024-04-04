/*
    Created by Judah Nava
    Created on 4/2/2024
*/

#ifndef __CPU_IDLE_READ_H__
#define __CPU_IDLE_READ_H__

#include <pthread.h>

#include "CPU_CACHE.h"

#define CPU_IDLE_BUFFER_SIZE    1024

struct cpu_meta
{
    int run ;
    long count ;
    pthread_mutex_t mutex ;
    double frequency ;
    const int size ;
    CPU_CACHE cache ;
    pthread_t idle_pid ;
};

// look into changing the name for constistency of the user.
typedef struct cpu_meta *CPU_Meta ;

//This starts the caching of the idle value.
CPU_Meta CPU_Idle_init(float timeOver, float frequency) ; //both be in seconds

void CPU_Idle_Get_Difference(
    CPU_Meta meta, unsigned long *idleDif, unsigned long *totalDif ) ;

void CPU_Idle_Print_Cache(CPU_Meta meta) ;

void CPU_Idle_Close(CPU_Meta meta) ;

#endif