/*
    The point of this program is to act like the work that 
    the worker nodes need to work on. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stress.h"

#define SIZE (1<<18)

void work()
{
    clock_t start, end ;
    double runTime ;
    int i, num = 1, primes = 0 ;
    int primesArray[SIZE] ;
    int count = 0 ;

    start = clock() ;

    while (num <= SIZE) { 
        i = 2; 
        while (i <= num) { 
            if(num % i == 0)
                break;
            i++; 
        }
        if (i == num)
        {
            primes++;
            primesArray[count] = i ;
            count++ ;
        }
        num++;
    }

    end = clock();
    runTime = (end - start) / (double) CLOCKS_PER_SEC;
    printf("This machine calculated all %d prime numbers under %d in %g seconds\n", primes, SIZE, runTime);

}