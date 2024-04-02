/*
    Created by Judah Nava
    Created on 4/2/24 4:20 am
*/

#include <stdio.h>
#include <stdlib.h>

#include "CPU_CACHE.h"

/*
    Note: the size needs to be constant thruought the program.
*/

CPU_CACHE CPU_CACHE_Init(int size)
{
    // Makes an empty cache
    CPU_CACHE last = NULL ;

    // adds the nodes the the empty cache
    for (int i = 0; i < size; i++)
        last = CPU_CACHE_Add_Node(last) ;
    
    return last ;
}

CPU_CACHE CPU_CACHE_Add_Node(CPU_CACHE last)
{
    CPU_CACHE newNode = 
        (CPU_CACHE) malloc(sizeof(struct CPU_CACHE_NODE)) ;
    
    newNode->idle = 0 ;
    newNode->total = 0 ;

    if (last == NULL)
    {
        // last->next = newNode ; //There is only one node at this point.
        last = newNode ;
        newNode->next = last ;
    }
    else
    {
        // Add the new node to the end and update the last
        // node's next pointer
        newNode->next = last->next;
        last->next = newNode;
        last = newNode; // Update the last pointer to the
                        // new node
    }

    return last ;
}

// This needs to be called in a muxtex lock
void CPU_CACHE_Get_Difference(
        CPU_CACHE last, unsigned long *idle, unsigned long *total )
{
    *idle = last->idle - last->next->idle ;
    *total = last->total - last->next->total ;
}

// This needs to be called in a muxex lock
CPU_CACHE CPU_CACHE_Update_Values(
        CPU_CACHE last, const unsigned long idle, const unsigned long total)
{
    last = last->next ;
    last->idle = idle ;
    last->total = total ;
    return last ;
}

void CPU_CACHE_Free(CPU_CACHE last, int size)
{
    CPU_CACHE tmp = last ;

    // This should leave one left
    for (int i = 0; i < (size-1); i++)
    {
        tmp = tmp->next ;
        free(last) ;
        last = tmp ;
    }

    free(last) ;
}

void CPU_CACHE_Display(CPU_CACHE last)
{
    if (last == NULL)
    {
        printf("List is empty.\n") ;
        return ;
    }

    CPU_CACHE temp = last->next ;

    do
    {
        printf("idle: %ld, total: %ld\n", temp->idle, temp->total) ;
        temp = temp->next ;
    } while (temp != last->next);
}