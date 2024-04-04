// This was provided by chatGPT
// Prompt: is there a way to read the "top" command in Linux and take its output into C into different variables
// Modified by Judah Nava
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int find_nth_occurrence(const char *str, char target, int n) ;

int main() {
    FILE *fp;
    char buffer[MAX_LINE_LENGTH] ;
    char buffer2[MAX_LINE_LENGTH] ;
    int check1, check2 ;
    int indexCPU1, indexCPU2 ;
    double idle, freeRAM ;
    int count ;
    
    for (int i = 0; i < 50; i++)
    {
        count = -1 ;
        // Open the top command in read mode through a pipe
        fp = popen("top -n 1 -b -Em", "r");
        if (fp == NULL) {
            fprintf(stderr, "Failed to run top command\n");
            exit(1);
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            count++ ;
            if(!((count == 2) || (count == 3)))
            {
                
                continue;
            }
            if (count == 2)
            {
                indexCPU1 = find_nth_occurrence(buffer, ',',3) ;
                indexCPU2 = find_nth_occurrence(buffer, ',',4) ;
                strncpy(buffer2, buffer+indexCPU1+1, indexCPU2-indexCPU1-3) ;
                idle = strtod(buffer2, NULL) ;
                printf("%lf\n", idle) ;
            }
            else if (count == 3)
            {
                indexCPU1 = find_nth_occurrence(buffer, ',',1) ;
                indexCPU2 = find_nth_occurrence(buffer, ',',2) ;
                strncpy(buffer2, buffer+indexCPU1+1, indexCPU2-indexCPU1-1) ;
                // printf("%s\n", buffer2) ;
                freeRAM = strtod(buffer2, NULL) ;
                printf("%lf\n", freeRAM) ;
                break;
            }
        }
        
        // Close the pipe
        pclose(fp);
    }
    return 0;
}

int find_nth_occurrence(const char *str, char target, int n) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == target) {
            count++;
            if (count == n) {
                return i; // Return the index of the nth occurrence
            }
        }
    }
    return -1; // If nth occurrence not found
}


/*
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st 
MiB Mem :   7626.4 total,   6326.2 free,    971.7 used,    553.7 buff/cache     
MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.   6654.7 avail Mem 
*/