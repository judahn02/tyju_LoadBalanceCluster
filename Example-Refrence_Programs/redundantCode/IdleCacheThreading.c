
#include <pthread.h>
#include <stdio.h>

#include "CPU_Idle_Read.h"


//Making a new library called CPU_Idle_Read
int main(int argc, char **argv)
{
    //Initialize
    pthread_t tid; 
    CPU_Meta meta ;
    int loop = 1 ;
    int userInput ; 

    //setup and start thread
    meta = (CPU_Meta) malloc(sizeof(struct cpu_meta)) ;
    meta->run = 1 ;
    meta->count = 0 ;
    if (pthread_mutex_init(&(meta->mutex), NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    //This is now implemented in just the library, no main should need to refrence it.
    //pthread_create(&tid, NULL, idleCacheLoad, (void *)meta) ;

    //user menu
    while (loop)
    {
        printf("Please enter 1 or 0: 1 to get current count, 0 to exit.: ") ;
        if (scanf("%d", &userInput) == 1) {
            if (userInput == 1)
            {
                pthread_mutex_lock(&(meta->mutex)) ;
                printf("Current count is: %d\n", meta->count) ;
                // This should not need a mutex lock but it feels like good practice.
                pthread_mutex_unlock(&(meta->mutex)) ;
            }
            else if (userInput == 0)
            {
                meta->run = 0 ;
                break ;
            }
            else
                printf("That was an interger but not 1 or 0 :(.\n") ;
                
        } else {
            printf("Invalid input. Please enter an integer.\n");
        }
    }


    //join thread
    pthread_join(tid, NULL) ;


    //free memmory
    pthread_mutex_destroy(&(meta->mutex)) ;
    free(meta) ;

    return 0 ;
}