#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTSet.h"

#define BUFFER 200

int compare_strings(Pointer a, Pointer b) {
    return strcmp((char *)a, (char *)b);
}

int main(void) {

    // Creating a Set
    Set Lines = set_create(compare_strings, free);

    // Reading line from stdin
    char *line = malloc(BUFFER*sizeof(char));
    while (fgets(line, BUFFER+1, stdin) != NULL) {
        set_insert(Lines, line);
        SetNode node = set_find_node(Lines, line);
        // if line is the biggest print none
        if (node == set_last(Lines))
            printf("<none>\n");
        // else print the next, which is the next biggest
        else
            printf("%s", (char *)set_node_value(Lines, set_next(Lines, node)));  
        // allocate memory for a new line
        line = malloc(BUFFER*sizeof(char));
    }

    // free all allocated memory
    free(line);
    set_destroy(Lines);

    return 0;
}