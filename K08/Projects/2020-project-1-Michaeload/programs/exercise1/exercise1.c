#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 100000
#define BUFFER 20

int main(void) {

    // Allocate memory for the lines to be read
    char **line = malloc(LINES * sizeof(char *));
    for (int i = 0; i < LINES; i++)
        line[i] = malloc(sizeof(BUFFER));

    // Initialize the array to '\0'
    for (int i = 0; i < LINES; i++)
        for (int j = 0; j < BUFFER; j++)
            line[i][j] = '\0';

    // Reading lines from stdin
    int line_counter = 0;
    while (fgets(line[line_counter], BUFFER+1, stdin) != NULL) {
        int counter = 0;
        // search the array for the line read
        for (int i = 0; i < line_counter; i++)
            if (!strcmp(line[i], line[line_counter]))
                counter++;
        printf("%d\n", counter);
        line_counter++;
    }

    // free all allocated memory
    for (int i = 0; i < LINES; i++)
        free(line[i]);
    free(line);
    
    return 0;
}
