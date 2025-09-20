#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"

int compare_ints(Pointer a, Pointer b) {
    return *(int *)a - *(int *)b;
}

// Δεσμεύει μνήμη για έναν ακέραιο, αντιγράφει το value εκεί και επιστρέφει pointer
int* create_int(int value) {
	int* pointer = malloc(sizeof(int));		// δέσμευση μνήμης
	*pointer = value;						// αντιγραφή του value στον νέο ακέραιο
	return pointer;
}

int main(void) {

    srand(time(NULL));

    printf("PriorityQueue:\n");

    PriorityQueue pq = pqueue_create(compare_ints, free, NULL);

    for (int i = 0; i < 20; i++) {
        pqueue_insert(pq, create_int(rand()%100));
    }
    for (int i = 0; i < 20; i++) {
        printf("%d\n", *(int *)pqueue_max(pq));
        pqueue_remove_max(pq);
    }
    pqueue_destroy(pq);

    printf("Set:\n");

   Set set = set_create(compare_ints, free);

    for (int i = 0; i < 20; i++) {
        int *value = create_int(rand()%100);
        if (set_find_node(set, value) == SET_EOF) {
            set_insert(set, value);
            i--;
            continue;
        }
        free(value);
    }

    SetNode node = set_first(set);
    for (int i = 0; i < 20; i++) {
        printf("%d\n", *(int *)set_node_value(set, node));
        node = set_next(set, node);
    }

    set_destroy(set);
}