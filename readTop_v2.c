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
    char buffer[MAX_LINE_LENGTH];
    
    // Open the top command in read mode through a pipe
    fp = popen("top -n 1 -b -Em", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run top command\n");
        exit(1);
    }

    // Read the output line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Example: print each line
        

        // Here you can parse the output and extract the information you need
        // For example, you can use string manipulation functions like strtok()

        // Example: tokenize the line using space as delimiter
        char *token = strtok(buffer, " ");
        // if((!strcmp(token, "\%Cpu(s):")) || (!strcmp(token, "MiB")))
        //     printf("%s", buffer);
        if((!strcmp(token, "\%Cpu(s):")) || (!strcmp(token, "MiB")))
            while (token != NULL) {
                // Process each token (e.g., store them in different variables)
                printf("%s", token);

                // Move to the next token
                token = strtok(NULL, " ");
            }
    }

    // Close the pipe
    pclose(fp);

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