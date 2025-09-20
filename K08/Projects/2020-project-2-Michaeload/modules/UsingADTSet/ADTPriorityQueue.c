#include <stdlib.h>
#include <string.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"

struct priority_queue {
    Set set;
    CompareFunc compare;
    CompareFunc compare_nodes;
};

struct priority_queue_node {
    Pointer value;
    PriorityQueue pqueue;
};

static int compare_nodes(Pointer a, Pointer b) {
    PriorityQueueNode node_a = a;
    PriorityQueueNode node_b = b;
    return node_a->pqueue->compare(node_a->value, node_b->value);
}

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
    
    PriorityQueue pqueue = malloc(sizeof(*pqueue));
    pqueue->set = set_create(compare_nodes, destroy_value);
    pqueue->compare_nodes = compare_nodes;
    pqueue->compare = compare;

    if (values == NULL)
        return pqueue;

    for (int i = 0; i < vector_size(values); i++) {
        PriorityQueueNode node = malloc(sizeof(*node));
        node->value = vector_get_at(values, i);
        node->pqueue = pqueue;
        set_insert(pqueue->set, node);
    }

    return pqueue;    
}

int pqueue_size(PriorityQueue pqueue) {
    return set_size(pqueue->set);
}

Pointer pqueue_max(PriorityQueue pqueue) {
    PriorityQueueNode node = set_node_value(pqueue->set, set_last(pqueue->set));
    return node->value;
}

PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value) {

    PriorityQueueNode node = malloc(sizeof(*node));
    node->value = value;
    node->pqueue = pqueue;

    set_insert(pqueue->set, node);
    
    return node;
}

void pqueue_remove_max(PriorityQueue pqueue) {
    PriorityQueueNode node = set_node_value(pqueue->set, set_last(pqueue->set));
    set_remove(pqueue->set, node);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
    return set_set_destroy_value(pqueue->set, destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue) {
    pqueue_set_destroy_value(pqueue, free);
    set_destroy(pqueue->set);
    free(pqueue);
}

Pointer pqueue_node_value(PriorityQueue set, PriorityQueueNode node) {
    return node->value;
}

void pqueue_remove_node(PriorityQueue pqueue, PriorityQueueNode node) {
    free(node->value);
    set_remove(pqueue->set, node);
}

void pqueue_update_order(PriorityQueue pqueue, PriorityQueueNode node) {
    return;
}