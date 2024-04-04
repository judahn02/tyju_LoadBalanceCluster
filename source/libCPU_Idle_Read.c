/*
    Created by Judah Nava
    Created on 4/4/2024
*/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CPU_Idle_Read.h"
#include "CPU_CACHE.h"

struct CPU_M {
    unsigned long user ;
    unsigned long nice ;
    unsigned long system ;
    unsigned long idle ;
    unsigned long iowait ;
    unsigned long irq ;
    unsigned long softirq ;
};
typedef struct CPU_M CPU_M ;


//These do not need to be called outside the library
void *idleCacheLoad(void *vargp) ;

void CPU_M_Load_From_Token(char*, CPU_M*) ;

void loadBufferFromProcStat(char*) ;

CPU_Meta CPU_Idle_init(float timeOver, float frequency)
// This will initialize an object of CPU_Meta and load
//  all the needed values within that object. Then it will
//  push a copy of it to the thread and start it.
{ 
    CPU_Meta meta ;
    int *size ;
    
    //setup and start thread
    meta = (CPU_Meta) malloc(sizeof(struct cpu_meta)) ;
    meta->run = 1 ;
    meta->count = 0 ;
    if (pthread_mutex_init(&(meta->mutex), NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        exit(1) ;
    }
    meta->frequency = frequency ;
    size = (int *)&(meta->size) ;
    *size = ceil(timeOver/frequency) ;
    meta->cache = CPU_CACHE_Init(*size) ;

    pthread_create(&(meta->idle_pid), NULL, idleCacheLoad, (void *)meta) ;

    return meta ;
}

void CPU_Idle_Get_Difference(
    CPU_Meta meta, unsigned long *idleDif, unsigned long *totalDif )
{
    pthread_mutex_lock(&(meta->mutex)) ;
    // printf("Current count in meta is: %ld\n", meta->count) ;
    CPU_CACHE_Get_Difference(meta->cache, idleDif, totalDif) ;
    pthread_mutex_unlock(&(meta->mutex)) ;
}

void CPU_Idle_Print_Cache(CPU_Meta meta)
{
    pthread_mutex_lock(&(meta->mutex)) ;
    printf("Current count in meta is: %ld\n", meta->count) ;
    CPU_CACHE_Display(meta->cache) ;
    pthread_mutex_unlock(&(meta->mutex)) ;
}

void CPU_Idle_Close(CPU_Meta meta)
{
    meta->run = 0 ;
    pthread_join(meta->idle_pid, NULL) ;
    CPU_CACHE_Free(meta->cache, meta->size) ;
    pthread_mutex_destroy(&(meta->mutex)) ;
    free(meta) ;
}

void *idleCacheLoad(void *vargp)
{
    CPU_Meta meta = (CPU_Meta)vargp ;

    struct timespec delay;
    delay.tv_sec = 0;              // Seconds
    delay.tv_nsec = 100000000 * meta->frequency ;     // Nanoseconds (0.2 seconds)

    char buffer[CPU_IDLE_BUFFER_SIZE] ;
    char *token ;
    CPU_M cpuMeta ;
    unsigned long total ;

    while(meta->run)
    {
        loadBufferFromProcStat(buffer) ;

        token = strtok(buffer, " ") ;

        CPU_M_Load_From_Token(token, &cpuMeta) ;

        total = cpuMeta.user + cpuMeta.nice + cpuMeta.system + 
                    cpuMeta.idle + cpuMeta.iowait + cpuMeta.irq + cpuMeta.softirq ;

        pthread_mutex_lock(&(meta->mutex)) ;
        meta->cache = CPU_CACHE_Update_Values(meta->cache, cpuMeta.idle, total) ;
        meta->count++ ;
        pthread_mutex_unlock(&(meta->mutex)) ;

        nanosleep(&delay, NULL) ;
    }
    printf("idleCacheLoad is ending.\n") ;
    pthread_exit(NULL) ; //not sure if needed
}

void CPU_M_Load_From_Token(char *token, CPU_M *cpuMeta)
{
    token = strtok(NULL, " ") ;
    cpuMeta->user = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->nice = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->system = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->idle = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->iowait = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->irq = strtoul(token, NULL, 10) ;

    token = strtok(NULL, " ") ;
    cpuMeta->softirq = strtoul(token, NULL, 10) ;
    // tests if the CPU_M_Load_From_Token is correct, it is on WSL Debian Lenovo Laptop Judahs
    /*
        printf("%ld, %ld, %ld, %ld, %ld, %ld, %ld\n",
            cpuMeta->user, cpuMeta->nice, cpuMeta->system, cpuMeta->idle, 
            cpuMeta->iowait, cpuMeta->irq, cpuMeta->softirq) ;
    */
}


void loadBufferFromProcStat(char *buffer)
/*
    This program pulls the first line from /proc/stat
    and loads it into buffer. 
    /proc is a virtual directory that allows access to
    much of the metadata of the computer.
*/
{
    FILE *fp ;

    // Opens pipe
    fp = popen("cat /proc/stat", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run 'cat /proc/stat' command\n");
        exit(1);
    }

    // loads buffer until it hits the first line.
    fscanf(fp, "%[^\n]", buffer) ;

    // Use for testing
    // printf("%s\n", buffer) ;
    pclose(fp);
}
