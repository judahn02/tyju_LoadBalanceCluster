

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024

int main()
{
    FILE *fp ;
    char buffer[MAX_LINE_LENGTH] ;
    int count, count2 = 0;
    double speed ;
    double total = 0 ;


    fp = popen("cat /proc/cpuinfo | grep Hz", "r") ;
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n") ;
        exit(1) ;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);

        char *token = strtok(buffer, " ") ;

        count = 0 ;
        while (token != NULL)
        {
            if (count == 2)
            {
                printf("Token:-%s-\n", token) ;
                speed = strtod((const char*)token, NULL) ;
                printf("Speed: %f\n", speed) ;
                count2++ ;
                total += (speed/1000) ;
            }
            

            token = strtok(NULL, " ") ;
            count++ ;
        }
    }
    if (errno == ERANGE)
            printf("The value provided was out of range\n");
    printf("Average total: %f\n", total/count2) ;
    pclose(fp) ;
    return 0 ;
}