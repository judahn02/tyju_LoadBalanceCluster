#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the end of the line
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Perform operation on each line (in this case, print it)
        printf("Line: %s\n", line);
    }

    fclose(file);
    return 0;
}
