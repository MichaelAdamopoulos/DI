#include <sys/shm.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#define PACKETSIZE 15
#define PACKETNUM 10
#define BUFFERSIZE PACKETNUM * PACKETSIZE
#define FILENAME "messenger.c"
#define RESULT_ERROR -1

struct Shared {
    // Semaphores to handle producing/consuming packets
    sem_t prod_a;
    sem_t prod_b;
    sem_t cons_a;
    sem_t cons_b;

    // Semaphores to handle input/output from terminal
    sem_t write_a;
    sem_t write_b;
    sem_t read_a;
    sem_t read_b;

    // Number of packets needed for each input
    int packet_a;
    int packet_b;      
    
    // Buffer to hold each packet
    char buffer_a[PACKETSIZE];
    char buffer_b[PACKETSIZE];

    // Variables to count messages produced/consumed
    int prod_count_a;
    int prod_count_b;
    int cons_count_a;
    int cons_count_b;

    // Variables to count packets
    int pacnum_a;
    int pacnum_b;

    // Variables for time statistics
    time_t time_a;
    time_t time_b;
};

struct Shared *shared;

pthread_t prodA;
pthread_t consA;
pthread_t prodB;
pthread_t consB;

void *consumerA();
void *producerA();
void *consumerB();
void *producerB();

void print_A();
void print_B();

int main(void) {

    // Variable to identify which process is running
    bool startingProcess = true;

    // Create shared memory key
    key_t key = ftok(FILENAME, 1);
    if (key == RESULT_ERROR) {
        printf("Failed to create key!\n");
        return RESULT_ERROR;
    }

    // Make shared memory segment
    // If one already exists, find it instead
    int id = shmget(key, sizeof(struct Shared), IPC_CREAT | IPC_EXCL | 0666);
    if (errno == EEXIST) {
        id = shmget(key, sizeof(struct Shared), 0666);
        startingProcess = false;
    }

    // Attach shared memory segment
    shared = (struct Shared *)shmat(id, NULL, 0);
    if (shared == (void *) RESULT_ERROR) {
        printf("Failed to attach shared memory segment!\n");
    }

    // Initialize semaphores
    if (startingProcess) {
        sem_init(&(shared->prod_a), 1, 1);
        sem_init(&(shared->prod_b), 1, 1);
        sem_init(&(shared->cons_a), 1, 0);
        sem_init(&(shared->cons_b), 1, 0);

        sem_init(&(shared->write_a), 1, 1);
        sem_init(&(shared->write_b), 1, 1);
        sem_init(&(shared->read_a), 1, 0);
        sem_init(&(shared->read_b), 1, 0);
    }

    // Create threads
    if (startingProcess) {
        if (pthread_create(&prodA, NULL, producerA, NULL)) {
            printf("Failed to create producer thread!\n");
            return RESULT_ERROR;
        }
        if (pthread_create(&consA, NULL, consumerA, NULL)) {
            printf("Failed to create consumer thread!\n");
            return RESULT_ERROR;
        }
    }
    else {
        if (pthread_create(&prodB, NULL, producerB, NULL)) {
            printf("Failed to create producer thread!\n");
            return RESULT_ERROR;
        }
        if (pthread_create(&consB, NULL, consumerB, NULL)) {
            printf("Failed to create consumer thread!\n");
            return RESULT_ERROR;
        }
    }

    // Join threads
    if (startingProcess) {
        if (pthread_join(prodA, NULL)) {
            printf("Failed to join producer thread!\n");
            return RESULT_ERROR;
        }

        if (pthread_join(consA, NULL)) {
            printf("Failed to join consumer thread!\n");
            return RESULT_ERROR;
        }
    }
    else {
        if (pthread_join(prodB, NULL)) {
            printf("Failed to join producer thread!\n");
            return RESULT_ERROR;
        }

        if (pthread_join(consB, NULL)) {
            printf("Failed to join consumer thread!\n");
            return RESULT_ERROR;
        }
    }

    // Detach shared memory segment
    if (shmdt((void *) shared) == RESULT_ERROR) {
         printf("Failed to detach shared memory segment!\n");
        return RESULT_ERROR;
    }

    // Destroy semaphores
    if (startingProcess) {
        sem_destroy(&(shared->prod_a));
        sem_destroy(&(shared->prod_b));
        sem_destroy(&(shared->cons_a));
        sem_destroy(&(shared->cons_b));

        sem_destroy(&(shared->write_a));
        sem_destroy(&(shared->write_b));
        sem_destroy(&(shared->read_a));
        sem_destroy(&(shared->read_b));
    }

    // Delete shared memory segment
    if (startingProcess)
        shmctl(id, IPC_RMID, NULL);

    return 0;
}

void *producerA() {

    // Initialize counters
    shared->prod_count_a = 0;
    shared->pacnum_a = 0;

    while (1) {
        // Reading from input
        sem_wait(&(shared->write_a));
        char input[BUFFERSIZE];
        fgets(input, BUFFERSIZE, stdin);

        // Number of packets needed for the input
        shared->packet_a = (!(strlen(input) % PACKETSIZE)) ? strlen(input) / PACKETSIZE : strlen(input) / PACKETSIZE + 1;
        
        // Producing packets
        sem_post(&(shared->read_b));
        for (int i = 0; i < shared->packet_a; i++) {
            sem_wait(&(shared->prod_a));
            (shared->pacnum_a)++;
            memcpy(shared->buffer_a, input + PACKETSIZE * i, sizeof(char) * PACKETSIZE);
            sem_post(&(shared->cons_b));
        }
        (shared->prod_count_a)++;

        // If "#BYE#" is given, cancel your process' other thread and exit
        if (!strcmp(input, "#BYE#\n")) {
            pthread_cancel(consA);
            print_A();
            pthread_exit(0);
        }
    }
}

void *consumerA() {

    // Initialize counters
    shared->cons_count_a = 0;
    shared->time_a = 0;

    time_t start, end;

    while (1) {
        // Writing to output
        time(&start);
        char output[BUFFERSIZE];
        
        // Consuming packets
        sem_wait(&(shared->read_a));
        for (int i = 0; i < shared->packet_b; i++) {
            sem_wait(&(shared->cons_a));
            // If first packet is consumed
            if (!i)
                time(&end);
            memcpy(output + PACKETSIZE * i, shared->buffer_b, sizeof(char) * PACKETSIZE);
            sem_post(&(shared->prod_b));
        }
        shared->time_a += end - start;
        (shared->cons_count_a)++;
        printf("%s", output);

        // If "#BYE#" is given, cancel your process' other thread and exit
        if (!strcmp(output, "#BYE#\n")) {
            pthread_cancel(prodA);
            print_A();
            pthread_exit(0);
        }
        sem_post(&(shared->write_b));
    }
}

void *producerB() {

    // Initialize counters
    shared->prod_count_b = 0;
    shared->pacnum_b = 0;

    while (1) {
        // Reading from input
        sem_wait(&(shared->write_b));
        char input[BUFFERSIZE];
        fgets(input, BUFFERSIZE, stdin);

        // Number of packets needed for the input
        shared->packet_b = (!(strlen(input) % PACKETSIZE)) ? strlen(input) / PACKETSIZE : strlen(input) / PACKETSIZE + 1;
        
        // Producing packets
        sem_post(&(shared->read_a));
        for (int i = 0; i < shared->packet_b; i++) {
            sem_wait(&(shared->prod_b));
            (shared->pacnum_b)++;
            memcpy(shared->buffer_b, input + PACKETSIZE * i, sizeof(char) * PACKETSIZE);
            sem_post(&(shared->cons_a));
        }
        (shared->prod_count_b)++;

        // If "#BYE#" is given, cancel your process' other thread and exit
        if (!strcmp(input, "#BYE#\n")) {
            pthread_cancel(consB);
            print_B();
            pthread_exit(0);
        }
    }
}

void *consumerB() {

    // Initialize counters
    shared->cons_count_b = 0;
    shared->time_a = 0;

    time_t start, end;

    while (1) {
        // Writing to output
        time(&start);
        char output[BUFFERSIZE];

        // Consuming packets
        sem_wait(&(shared->read_b));
        for (int i = 0; i < shared->packet_a; i++) {
            sem_wait(&(shared->cons_b));
            // If first packet is consumed
            if (!i)
                time(&end);
            memcpy(output + PACKETSIZE * i, shared->buffer_a, sizeof(char) * PACKETSIZE);
            sem_post(&(shared->prod_a));
        }
        shared->time_b += end - start;
        (shared->cons_count_b)++;
        printf("%s", output);

        // If "#BYE#" is given, cancel your process' other thread and exit
        if (!strcmp(output, "#BYE#\n")) {
            pthread_cancel(prodB);
            print_B();
            pthread_exit(0);
        }
        sem_post(&(shared->write_a));
    }
}

// Functions to print statistics
void print_A() {
    printf("Process A produced %d messages\n", shared->prod_count_a);
    printf("Process A consumed %d messages\n", shared->cons_count_a);
    // If counters are not 0
    if (shared->prod_count_a)
        printf("Process A produced %d total packages with an average of %.2f per message\n", shared->pacnum_a, (float) shared->pacnum_a / shared->prod_count_a);
    if (shared->cons_count_a)
        printf("Process A waited on average %ld seconds for each first packet\n", shared->time_a / shared->cons_count_a);
}

void print_B() {
    printf("Process B produced %d messages\n", shared->prod_count_b);
    printf("Process B consumed %d messages\n", shared->cons_count_b);
    // If counters are not 0
    if (shared->prod_count_b)
        printf("Process B produced %d total packages with an average of %.2f per message\n", shared->pacnum_b, (float) shared->pacnum_b / shared->prod_count_b);
    if (shared->cons_count_b)
        printf("Process B waited on average %ld seconds for each first packet\n", shared->time_b / shared->cons_count_b);
}