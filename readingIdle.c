#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
    This program demonstrates how reading and processing
    the value of idle will look like.
*/

// headder added by the makefile
#include "CPU_CACHE.h"

#define MAX_LINE_LENGTH 1024

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

void CPU_M_Load_From_Token(char*, CPU_M*) ;

void loadBufferFromProcStat(char*) ;

int main(int argc, char **argv)
// This program nees to utilize the Cache.
{
    int size = 10 ;
    CPU_CACHE cache = CPU_CACHE_Init(size) ;
    unsigned long idleDif, totalDif ;

    char buffer[MAX_LINE_LENGTH] ;
    char *token ;
    CPU_M cpuMeta ;
    unsigned long total ;
    long double percent ;

    struct timespec delay;
    delay.tv_sec = 0;              // Seconds
    delay.tv_nsec = 100000000 * 2;     // Nanoseconds (0.2 seconds)

    
    for (int i = 0; i < 20; i++)
    {
        
        loadBufferFromProcStat(buffer) ;

        token = strtok(buffer, " ") ;

        CPU_M_Load_From_Token(token, &cpuMeta) ;

        total = cpuMeta.user + cpuMeta.nice + cpuMeta.system + 
            cpuMeta.idle + cpuMeta.iowait + cpuMeta.irq + cpuMeta.softirq ;

        cache = CPU_CACHE_Update_Values(cache, cpuMeta.idle, total) ;

        nanosleep(&delay, NULL) ;
    }

    CPU_CACHE_Display(cache) ;

    CPU_CACHE_Get_Difference(cache, &idleDif, &totalDif) ;
    percent = (long double) idleDif / totalDif * 100 ;
    printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
    printf("the idle percent over a second is: %Lf\% \n", percent) ;

    CPU_CACHE_Free(cache, size) ;
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
        fprintf(stderr, "Failed to run top command\n");
        exit(1);
    }

    // loads buffer until it hits the first line.
    fscanf(fp, "%[^\n]", buffer) ;

    // Use for testing
    // printf("%s\n", buffer) ;
    pclose(fp);
}

