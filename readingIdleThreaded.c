

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct cpu_meta
{
    int run ;
    int count ;
    pthread_mutex_t mutex ;
};

typedef struct cpu_meta *CPU_Meta ;

void *templeteCount(void *vargp)
{
    CPU_Meta meta = (CPU_Meta)vargp ;

    while(meta->run)
    {
        pthread_mutex_lock(&(meta->mutex)) ;
        meta->count++ ;
        pthread_mutex_unlock(&(meta->mutex)) ;
        sleep(1) ;
    }
    printf("templeteCount is ending.\n") ;
}

int main(int argc, char **argv)
{
    pthread_t tid; 
    CPU_Meta meta ;
    int loop = 1 ;
    int userInput ; 

    meta = (CPU_Meta) malloc(sizeof(struct cpu_meta)) ;
    meta->run = 1 ;
    meta->count = 0 ;
    if (pthread_mutex_init(&(meta->mutex), NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }
    pthread_create(&tid, NULL, templeteCount, (void *)meta) ;

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

    //Exiting
    pthread_join(tid, NULL) ;
    pthread_mutex_destroy(&(meta->mutex)) ;
    free(meta) ;

    return 0 ;

}

