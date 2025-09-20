#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

struct Job {
    char *jobID;    // ex. Job_XX
    char **job;     // ex. [ls,-l]
    int queuePosition;
    int pid;
    char *info;     // ex. <job_XX,ls-l,1>
};

struct Node {
    struct Job *job;
    struct Node *next;
};

struct Queue {
    struct Node *head;
    struct Node *tail;
    int size;
};

// Create empty Queue
struct Queue *createQueue();

// Create empty Node
struct Node *createNode(struct Job *);

// Push Job
void push(struct Queue *, struct Job *);

// Pop Job
struct Job *pop(struct Queue *);

// Pop Job based on specific PID
struct Job *popPID(struct Queue *, int);

// Pop Job based on specific ID
struct Job *popID(struct Queue *, char *);

// Print Job
void printJob(struct Job *);

// Print all Jobs
void printQueue(struct Queue *);

// Return Job at specific index
struct Job *getJob(struct Queue *, int);
