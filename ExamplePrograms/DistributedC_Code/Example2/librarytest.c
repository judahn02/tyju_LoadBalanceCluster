#include "mycode.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc > 1) { // There is always atleast one argument
        printf("%s\n", argv[1]) ;
        printf("%s\n", reverse(argv[1])) ;
        return 0 ;
    }
    printf("missing argument\n") ;
    return 0 ;

}