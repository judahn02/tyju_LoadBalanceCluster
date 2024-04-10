#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define SIZE (1<<18)

int main(int argc, char **argv) {
    // pid_t wpid ;
    // int status = 0 ;

//    fork() ; // 2
//    fork() ; // 4
//    fork() ; // 8

    clock_t start, end;
    double runTime;
    start = clock();
    int i, num = 1, primes = 0;
    int primesArray [SIZE] ;
    int count = 0 ;

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

    return 0 ;
}
