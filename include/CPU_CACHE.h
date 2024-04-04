
/*
    Created by Judah Nava
    Created on 4/2/2024
    Special thanks to geeksforgekks
    assisting link: https://www.geeksforgeeks.org/how-to-create-a-circular-linked-list-in-c/

*/

#ifndef __CPU_CACHE_H__
#define __CPU_CACHE_H__

struct CPU_CACHE_NODE
{
    unsigned long idle ;
    unsigned long total ;
    struct CPU_CACHE_NODE *next ;
};

typedef struct CPU_CACHE_NODE* CPU_CACHE ;

CPU_CACHE CPU_CACHE_Init(int size) ;

CPU_CACHE CPU_CACHE_Add_Node(CPU_CACHE last) ;

// This needs to be called in a muxtex lock
void CPU_CACHE_Get_Difference(
        CPU_CACHE last, unsigned long *idle, unsigned long *total ) ;

// This needs to be called in a muxex lock
CPU_CACHE CPU_CACHE_Update_Values(
        CPU_CACHE last, const unsigned long idle, const unsigned long total) ;

void CPU_CACHE_Free(CPU_CACHE last, int size) ;

void CPU_CACHE_Display(CPU_CACHE last) ;

#endif