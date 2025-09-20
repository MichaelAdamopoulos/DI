#define _DEFAULT_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "queue.h"

#define PIPE_PERMS 0666
#define TXT_PERMS 0644
#define TXT "jobExecutorServer.txt"
#define COMMAND_PIPE "./command"
#define INFO_PIPE "./info"
#define ERROR -1

// Struct to monitor jobs
struct Jobs {
    struct Queue *queuedJobs;
    struct Queue *runningJobs;
    int concurrency;
    int ids;    // the id of the latest job sent
};

// Functions to start and close server
// Arguments are fd or pointers to fd
int starting(int *, int *, int *);
int closing(int, int, int);

// Free Job memory
void freeJob(struct Job *);
