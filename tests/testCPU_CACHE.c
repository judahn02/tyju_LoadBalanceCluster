
#include <stdio.h>

#include "CPU_CACHE.h"

//The call for the AddNode is impicit in the Init.

int main(int argc, char **argv)
{
    int size = 5 ;
    unsigned long idleDif, totalDif ;
    CPU_CACHE cache = CPU_CACHE_Init(size) ;

    for (int i = 0; i < 15; i++)
        cache = CPU_CACHE_Update_Values(cache, i, i*100) ;

    CPU_CACHE_Get_Difference(cache, &idleDif, &totalDif) ;

    
    printf("!! This is only a test of the cache library. !!\n") ;
    CPU_CACHE_Display(cache) ;
    printf("idle diff: %ld, total diff: %ld\n", idleDif, totalDif) ;
    printf("QQ This is only a test of the cache library. !!\n") ;

    CPU_CACHE_Free(cache, size) ;
}