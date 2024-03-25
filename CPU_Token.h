#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __CPU_TOKEN_H__
#define __CPU_TOKEN_H__

#define CPU_TOKEN_ARRAY_SIZE 10

struct CPU_info {
    unsigned long array[10] ;
} ;

void info_load(char *string, struct CPU_info *C_info);

#endif