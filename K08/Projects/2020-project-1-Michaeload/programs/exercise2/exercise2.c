#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTMap.h"

#define BUFFER 200

int* create_int(int value) {
	int* pointer = malloc(sizeof(int));
	*pointer = value;
	return pointer;
}

int compare_strings(Pointer a, Pointer b) {
    return strcmp((char *)a, (char *)b);
}

int main(void) {

    // Creating a Map
    Map Lines = map_create(compare_strings, free, free);

    // Reading lines from stdin
    char *line = malloc(sizeof(BUFFER));
    while (fgets(line, BUFFER+1, stdin) != NULL) {
        int *value = (int *)map_find(Lines, line);
        // if line exists, raise its value by 1
        if (value != NULL) {
            map_insert(Lines, line, create_int(++(*value)));
        }
        // else, insert it with value = 0
        else
            map_insert(Lines, line, create_int(0));
        printf("%d\n", *(int *)map_find(Lines, line));
        // allocate new memory for the next line
        line = malloc(sizeof(BUFFER));
    }

    // free all allocated memory
    free(line);
    map_destroy(Lines);

    return 0;
}