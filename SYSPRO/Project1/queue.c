#include "include/queue.h"

struct Queue *createQueue() {
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        perror("createQueue: Malloc failed");
        exit(ERROR);
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

struct Node *createNode(struct Job *job) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("createNode: Malloc failed");
        exit(ERROR);
    }
    newNode->job = job;
    newNode->next = NULL;

    return newNode;
}

void push(struct Queue *queue, struct Job *job) {
    
    struct Node *newNode = createNode(job);

    if (queue->size == 0) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

struct Job *pop(struct Queue *queue) {

    if (queue->size == 0) {
        return NULL;
    }

    queue->size--;

    struct Job *job = queue->head->job;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    return job;
}

struct Job *popPID(struct Queue *queue, int pid) {

    struct Node *current = queue->head;
    struct Node *previous = NULL;

    while (current != NULL && current->job->pid != pid) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    if (previous == NULL) {
        queue->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current->next == NULL) {
        queue->tail = previous;
    }

    queue->size--;

    return current->job;
}

struct Job *popID(struct Queue *queue, char jobID[7]) {

    struct Node *current = queue->head;
    struct Node *previous = NULL;

    while (current != NULL && strcmp(current->job->jobID, jobID)) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    if (previous == NULL) {
        queue->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current->next == NULL) {
        queue->tail = previous;
    }

    queue->size--;

    return current->job;
}

void printJob(struct Job *job) {
    printf("Job ID: %s\n", job->jobID);
    printf("Queue Position: %d\n", job->queuePosition);
    printf("Job: ");
    for (int i = 0; job->job[i] != NULL; i++) {
        printf("%s ", job->job[i]);
    }
    printf("\n");
}

void printQueue(struct Queue *queue) {
    printf("Queue Size: %d\n", queue->size);
    printf("Jobs in Queue:\n");
    struct Node *current = queue->head;
    while (current != NULL) {
        printJob(current->job);
        current = current->next;
    }
}

struct Job *getJob(struct Queue *queue, int index) {
    if (index < 0 || index >= queue->size) {
        return NULL;
    }
    struct Node *current = queue->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->job;
}