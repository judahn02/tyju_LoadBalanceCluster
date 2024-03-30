// This was provided by chatGPT
// Prompt: is there a way to read the "top" command in Linux and take its output into C into different variables
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main() {
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    
    // Open the top command in read mode through a pipe
    fp = popen("top -n 1 -b", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run top command\n");
        exit(1);
    }

    // Read the output line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Example: print each line
        printf("%s", buffer);

        // Here you can parse the output and extract the information you need
        // For example, you can use string manipulation functions like strtok()

        // Example: tokenize the line using space as delimiter
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            // Process each token (e.g., store them in different variables)
            printf("Token: %s\n", token);

            // Move to the next token
            token = strtok(NULL, " ");
        }
    }

    // Close the pipe
    pclose(fp);

    return 0;
}
