#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ADTVector.h"

#define N 10000

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int main(int argc, char *argv[]) {

    if (strcmp(argv[1], "real") == 0) {
        Vector vec = vector_create(0, free);
        for (int i = 1; i <= N; i++) {
            vector_insert_last(vec, create_int(rand()));
            printf("%d,%d\n", i, vector_steps(vec));
        }
        vector_destroy(vec);
    }
    else if (strcmp(argv[1], "amortized") == 0) {
        Vector vec = vector_create(0, free);
        int total_steps = 0;
        for (int i = 1; i <= N; i++) {
            vector_insert_last(vec, create_int(rand()));
            total_steps += vector_steps(vec);
            printf("%d,%d\n", i, total_steps/i);
        }
         vector_destroy(vec);
    }
    return 0;    
}