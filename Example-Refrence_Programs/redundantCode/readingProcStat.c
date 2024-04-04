
// #include <limits.h> // for ULONG_MAX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
//First make the loop and have it display
// to the screen.
{
    char buffer[MAX_LINE_LENGTH] ;
    char *token ;
    unsigned long total, total2, totalDifference ;
    unsigned long idleDifference ;
    CPU_M cpuMeta, cpuMeta2 ;
    long double percent ;

    loadBufferFromProcStat(buffer) ;

    //Load token
    token = strtok(buffer, " ") ;

    CPU_M_Load_From_Token(token, &cpuMeta) ;
    

    total = cpuMeta.user + cpuMeta.nice + cpuMeta.system + 
        cpuMeta.idle + cpuMeta.iowait + cpuMeta.irq + cpuMeta.softirq ;
    percent = (long double) cpuMeta.idle/(total) * 100 ;
    printf("idle: %ld, total: %ld\n", cpuMeta.idle, total) ; 
    printf("the total idle percent being: %Lf\% \n", percent) ;
    
    for (int i = 0; i < 10; i++)
    {
        sleep(1) ;
        loadBufferFromProcStat(buffer) ;
        token = strtok(buffer, " ") ;
        CPU_M_Load_From_Token(token, &cpuMeta2) ;
        total2 = cpuMeta2.user + cpuMeta2.nice + cpuMeta2.system + 
            cpuMeta2.idle + cpuMeta2.iowait + cpuMeta2.irq + cpuMeta2.softirq ;
        
        totalDifference = total2 - total ;
        idleDifference = cpuMeta2.idle - cpuMeta.idle ;
        percent = (long double) idleDifference / totalDifference * 100 ;
        printf("idle: %ld, total: %ld\n", cpuMeta2.idle, total2) ; 
        printf("idle Diff.: %ld, total Diff.: %ld\n", idleDifference, totalDifference) ;
        printf("the idle percent over a second is: %Lf\% \n", percent) ;

        total = total2 ;
        cpuMeta.idle = cpuMeta2.idle ;
        cpuMeta.iowait = cpuMeta2.iowait ;
        cpuMeta.irq = cpuMeta2.irq ;
        cpuMeta.nice = cpuMeta2.nice ;
        cpuMeta.softirq = cpuMeta2.softirq ;
        cpuMeta.system = cpuMeta2.system ;
        cpuMeta.user = cpuMeta2.user ;
    }


    return 0 ;

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

