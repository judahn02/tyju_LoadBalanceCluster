#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_ROWS 11
#define MAX_LINE_LENGTH 100

int main() {
    char input[] = "cpu 49155 0 38898 20520769 4387 0 9759 0 0 0 cpu 49159 0 38906 20522356 4387 0 9759 0 0 0 cpu 49162 0 38910 20523947 4387 0 9761 0 0 0";
    char* token;
    char* delimiter = " ";

    // Split the input string into tokens
    token = strtok(input, delimiter);
    int count = 0;

    while (token != NULL) {
        printf("%s ", token);
        count++;

        // Break into a new line after every 10 tokens
        if (count % NUM_ROWS == 0)
            printf("\n");

        token = strtok(NULL, delimiter);
    }

    return 0;
}

