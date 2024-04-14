
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RAM_read.h"


double RAM_freeRam()
{
    FILE *fp ;
    fp = fopen("/proc/meminfo", "r") ;
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to run command\n") ;
        exit(1) ;
    }
    
    unsigned long mem_free;
    double mem_free_mb = -1 ;

    // Loop through the lines in the file
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        // Use sscanf to parse the line looking for MemFree
        if (sscanf(line, "MemFree: %lu kB", &mem_free) == 1) {
            // If found, print the memory value and break the loop
            mem_free_mb = mem_free / 1024.0;
            // printf("MemFree: %.2f MB\n", mem_free_mb);
            break;
            
        }
    }
    
    
    fclose(fp) ;
    return mem_free_mb ;
}