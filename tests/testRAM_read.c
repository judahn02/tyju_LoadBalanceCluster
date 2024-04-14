
#include <stdio.h>

#include "RAM_read.h"


int main()
{
    double freeRam = RAM_freeRam() ;

    printf("%.2f MB \n", freeRam) ;

    return 0 ;
}