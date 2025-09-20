#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>

#define ERROR -1

#define BACKLOG_LIMIT 128               // maximum number of standby connections to be accepted
#define JOB_MAX_ARGS 100                // maximum arguments of a job
#define OUTPUT_FILE_NAME_MAX_LENGTH 32  // maximum name length of the .output files
#define INFO_LENGTH 128                 // for sending data to the commander

// Job
typedef struct {
    char *job;                  // command(ex. ls -l)
    int clientSocket;           // socket between commander and controller thread
    char jobID[7];              // job_XX
} Job;

int concurrency;
int totalJobs;                  // increasing number of jobs(for job_ID)
int runningJobs;                // jobs running atm
int serverSock;
bool running;                   // server running

pthread_t *workerThreads;       // pointer to workerThread pool
pthread_t mainThread;           

// Buffered jobs
typedef struct {
    int bufferSize;             // size of buffer
    int jobCount;               // number of queued jobs
    Job **Jobs;                 // pointer to an array of Jobs
} Buffer;

Buffer *buffer;

// Cond vars for change in concurrency or when the buffer becomes empty/full
// and mutexes for controllers, workers and change in concurrency
pthread_mutex_t controllerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t workerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t concurrencyMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t bufferNotFullCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferNotEmptyCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t concurrencyCond = PTHREAD_COND_INITIALIZER;

void *controller_thread(void *);
void *worker_thread(void *);

// Handler for exiting server signal sent by controller thread => close server
void server_exit_signal(int signal) {
    if (signal == SIGUSR1) {
        running = false;
        close(serverSock);
    }
}

// Main thread
int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Server: Not enough arguments!\n");
        exit(ERROR);
    }

    int portNum = atoi(argv[1]);
    int bufferSize = atoi(argv[2]);
    int threadPoolSize = atoi(argv[3]);

    if (bufferSize <= 0 || threadPoolSize <= 0) {
        printf("Server: Wrong arguments!\n");
        exit(ERROR);
    }

    concurrency = 1;
    totalJobs = 0;
    runningJobs = 0;
    running = true;

    // Initialize buffer for jobs
    buffer = (Buffer *)malloc(sizeof(Buffer));
    if (buffer == NULL) {
        printf("Server: Malloc for buffer struct failed!\n");
        exit(ERROR);
    }

    buffer->bufferSize = bufferSize;
    buffer->jobCount = 0;
    buffer->Jobs = (Job **)malloc(bufferSize * sizeof(Job *));

    if (buffer->Jobs == NULL) {
        printf("Server: Malloc for jobs array failed!\n");
        free(buffer);
        exit(ERROR);
    }

    for (int i = 0; i < bufferSize; i++)
        buffer->Jobs[i] = NULL;

    // Keep mainThread value so controller thread has access to it
    mainThread = pthread_self();

    // Initialize handler
    struct sigaction sa;
    sa.sa_handler = server_exit_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        printf("Server: Sigaction failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize worker threads' pool
    workerThreads = (pthread_t *)malloc(threadPoolSize * sizeof(pthread_t));
    for (int i = 0; i < threadPoolSize; i++)
        pthread_create(&workerThreads[i], NULL, worker_thread, NULL);

    // Create server
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        printf("Server: Socket creation failed!\n");
        exit(ERROR);
    }

    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr *)&server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(portNum);

    if (bind(serverSock, serverptr, sizeof(server)) < 0) {
        printf("Server: Bind failed!\n");
        close(serverSock);
        exit(ERROR);
    }

    if (listen(serverSock, BACKLOG_LIMIT) < 0) {
        printf("Server: Listen failed!\n");
        close(serverSock);
        exit(ERROR);
    }

    // While server is running accept connections and create controller thread
    while (running) {

        struct sockaddr_in client;
        struct sockaddr *clientptr = (struct sockaddr *)&client;
        socklen_t clientLength = sizeof(client);

        int *clientSock = malloc(sizeof(int));
        if (clientSock == NULL) {
            printf("Server: Malloc for clientSock failed!\n");
            continue;
        }

        // If accept fails but server is closing then we break the loop
        *clientSock = accept(serverSock, clientptr, &clientLength);
        if (*clientSock < 0) {
            free(clientSock);
            if (running)
                printf("Server: Accept failed!\n");
            else
                break;
        } 
        else {
            pthread_t thread;
            // We pass to the thread the clientSock so it can communicate with the commander
            pthread_create(&thread, NULL, controller_thread, clientSock);
        }
    }

    // Reach this part if server is closing

    // Signal all worker threads to wake up and collect them
    for (int i = 0; i < threadPoolSize; i++) {
        pthread_cond_broadcast(&bufferNotEmptyCond);
        pthread_join(workerThreads[i], NULL);
    }

    free(workerThreads);

    return 0;
}

// Controller thread
void *controller_thread(void *clientSock) {

    int controllerSock = *(int *)clientSock;
    free(clientSock);

    // Read the command, create a string that contains the job(ex. ls -l)
    // and an array for the first 2 args(we do not need more than 2 args for the if cases)
    int commandLength;

    if (read(controllerSock, &commandLength, sizeof(commandLength)) < 0) {
        close(controllerSock);
        pthread_exit(NULL);
    }

    commandLength = ntohl(commandLength);

    char *command = (char *)malloc(commandLength + 1);
    if (command == NULL) {
        close(controllerSock);
        pthread_exit(NULL);
    }

    if (read(controllerSock, command, commandLength) < 0) {
        free(command);
        close(controllerSock);
        pthread_exit(NULL);
    }

    // Create the jobString only if the command is an issueJob one
    char *jobString;
    command[commandLength] = '\0';
    if (strncmp(command, "issueJob", strlen("issueJob")) == 0) {
        jobString = (char *)malloc(commandLength - strlen("issueJob ") + 1);
        strcpy(jobString, command + strlen("issueJob "));
    }

    // Array for the 2 first args(maximum possible args needed)
    // ex. stop job_42 or poll or setConcurrency 8 etc.
    char *commandArray[2];
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL && i < 2) {
        commandArray[i++] = token;
        token = strtok(NULL, " ");
    }

    // Run command

    // issueJob
    if (!strcmp(commandArray[0], "issueJob")) {

        // Block other controllers
        pthread_mutex_lock(&controllerMutex);

        // Block while buffer is full
        while (buffer->jobCount == buffer->bufferSize)
            pthread_cond_wait(&bufferNotFullCond, &controllerMutex);

        // Create new job
        Job *newJob = malloc(sizeof(Job));
        if (newJob == NULL) {
            pthread_mutex_unlock(&controllerMutex);
            free(command);
            close(controllerSock);
            pthread_exit(NULL);
        }

        newJob->clientSocket = controllerSock;
        snprintf(newJob->jobID, 7, "job_%d", ++totalJobs);
        newJob->job = strdup(jobString);
        buffer->Jobs[buffer->jobCount++] = newJob;

        pthread_cond_signal(&bufferNotEmptyCond);

        pthread_mutex_unlock(&controllerMutex);

        // Send info 
        char info[INFO_LENGTH];
        snprintf(info, sizeof(info), "JOB <%s, %s> SUBMITTED\n", newJob->jobID, jobString);
        if (send(controllerSock, info, strlen(info), 0) < 0) {
            free(command);
            close(controllerSock);
            pthread_exit(NULL);
        }
    }

    // setConcurrency
    else if (!strcmp(commandArray[0], "setConcurrency")) {
        int newConcurrency = atoi(commandArray[1]);
        if (newConcurrency <= 0) {
            close(controllerSock);
            free(command);
            pthread_exit(NULL);
        }

        // Update concurrency and signal all workers
        pthread_mutex_lock(&concurrencyMutex);
        concurrency = newConcurrency;
        pthread_cond_broadcast(&concurrencyCond);
        pthread_mutex_unlock(&concurrencyMutex);

        // Send info
        char info[INFO_LENGTH];
        snprintf(info, sizeof(info), "CONCURRENCY SET AT %d\n", newConcurrency);
        if (send(controllerSock, info, strlen(info), 0) < 0) {
            free(command);
            close(controllerSock);
            pthread_exit(NULL);
        }

        // Ensure all data is sent and then close socket
        shutdown(controllerSock, SHUT_WR);
    }

    // stop
    else if (!strcmp(commandArray[0], "stop")) {

        char *jobID = commandArray[1];

        // job exists in buffer
        bool found = false;

        pthread_mutex_lock(&controllerMutex);

        // Search for job
        // If found, close the connection and remove it from buffer
        for (int i = 0; i < buffer->jobCount; i++) {
            if (!strcmp(buffer->Jobs[i]->jobID, jobID)) {
                close(buffer->Jobs[i]->clientSocket);

                free(buffer->Jobs[i]->job);
                free(buffer->Jobs[i]);

                // Shift the remaining jobs in the buffer
                for (int j = i; j < buffer->jobCount - 1; j++)
                    buffer->Jobs[j] = buffer->Jobs[j + 1];

                buffer->jobCount--;
                found = true;
                break;
            }
        }

        pthread_mutex_unlock(&controllerMutex);

        // Send info
        char info[INFO_LENGTH];

        if (found) {
            pthread_cond_signal(&bufferNotFullCond);
            snprintf(info, sizeof(info), "JOB %s REMOVED\n", jobID);
        } 
        else
            snprintf(info, sizeof(info), "JOB %s NOT FOUND\n", jobID);

        if (send(controllerSock, info, strlen(info), 0) < 0) {
            free(command);
            close(controllerSock);
            pthread_exit(NULL);
        }

        // Ensure all data is sent and then close socket
        shutdown(controllerSock, SHUT_WR);
    }

    // poll
    else if (!strcmp(commandArray[0], "poll")) {

        // Send info for each job
        pthread_mutex_lock(&controllerMutex);

        int jobCount = buffer->jobCount;
        char allJobsInfo[INFO_LENGTH * 10] = "";
        for (int i = 0; i < jobCount; i++) {
            char jobInfo[INFO_LENGTH];
            snprintf(jobInfo, sizeof(jobInfo), "<%s, %s>\n", buffer->Jobs[i]->jobID, buffer->Jobs[i]->job);
            strcat(allJobsInfo, jobInfo);
        }

        pthread_mutex_unlock(&controllerMutex);

        // Send info
        if (send(controllerSock, allJobsInfo, strlen(allJobsInfo), 0) < 0) {
            close(controllerSock);
            free(command);
            pthread_exit(NULL);
        }

        // Ensure all data is sent and then close socket
        shutdown(controllerSock, SHUT_WR);
    }
    
    // exit 
    else if (!strcmp(commandArray[0], "exit")) {

        pthread_mutex_lock(&controllerMutex);

        // Stop all buffered jobs and send termination info
        for (int i = 0; i < buffer->jobCount; i++) {
            char info[INFO_LENGTH];
            snprintf(info, sizeof(info), "SERVER TERMINATED BEFORE EXECUTION\n");
            send(buffer->Jobs[i]->clientSocket, info, strlen(info), 0);
            close(buffer->Jobs[i]->clientSocket);
            free(buffer->Jobs[i]->job);
            free(buffer->Jobs[i]);
        }
        buffer->jobCount = 0;

        // Signal workers to wake
        pthread_cond_broadcast(&bufferNotEmptyCond);

        pthread_mutex_unlock(&controllerMutex);

        // Send server termination info and kill it
        char info[INFO_LENGTH];
        snprintf(info, sizeof(info), "SERVER TERMINATED\n");
        if (send(controllerSock, info, strlen(info), 0) < 0) {
            close(controllerSock);
            free(command);
            pthread_exit(NULL);
        }

        shutdown(controllerSock, SHUT_WR);

        pthread_kill(mainThread, SIGUSR1);

    } 
    else close(controllerSock);

    free(command);

    return 0;
}

// Worker thread
void *worker_thread(void *arg) {
    while (1) {

        // Block other workers
        pthread_mutex_lock(&workerMutex);

        // Exit if server is closing
        if (!running) {
            pthread_mutex_unlock(&workerMutex);
            pthread_exit(NULL);
        }

        // Block when buffer is empty
        while (buffer->jobCount == 0 && running)
            pthread_cond_wait(&bufferNotEmptyCond, &workerMutex);

        // Block when runningJobs >= concurrency
        pthread_mutex_lock(&concurrencyMutex);
        while (runningJobs >= concurrency && running)
            pthread_cond_wait(&concurrencyCond, &concurrencyMutex);
        pthread_mutex_unlock(&concurrencyMutex);

        // Exit if server is closing after being unblocked
        if (!running) {
            pthread_mutex_unlock(&workerMutex);
            pthread_exit(NULL);
        }

        // New job
        runningJobs++;

        Job *job = buffer->Jobs[0];

        // Remove job from buffer (shift buffer left)
        for (int i = 0; i < buffer->jobCount - 1; i++)
            buffer->Jobs[i] = buffer->Jobs[i + 1];
        buffer->jobCount--;

        // Signal controller threads that jobs can be submitted
        pthread_cond_signal(&bufferNotFullCond);

        pthread_mutex_unlock(&workerMutex);

        // Create arguments' array
        char *args[JOB_MAX_ARGS];
        int argc = 0;
        char *token = strtok(job->job, " ");
        while (token != NULL && argc < JOB_MAX_ARGS) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // Run job
        int pid = fork();
        // Failed => revert changes
        if (pid < 0) {
            pthread_mutex_lock(&concurrencyMutex);
            runningJobs--;
            pthread_cond_signal(&concurrencyCond);
            pthread_mutex_unlock(&concurrencyMutex);
            continue;
        }
        // Child => create .output, dup2 the stdout/stderr and exec the job 
        else if (pid == 0) {
            char outputFileName[OUTPUT_FILE_NAME_MAX_LENGTH];
            sprintf(outputFileName, "%s.output", job->jobID);

            int filefd = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (filefd < 0)
                exit(ERROR);

            if (dup2(filefd, STDOUT_FILENO) < 0) {
                close(filefd);
                exit(ERROR);
            }

            if (dup2(filefd, STDERR_FILENO) < 0) {
                close(filefd);
                exit(ERROR);
            }

            close(filefd);

            execvp(args[0], args);
            exit(ERROR);
        }
        // Parent => wait for child, then read .output and send it to the commander
        // Also before exiting, signal workers that a job has ended so they can start another
        else {
            if (waitpid(pid, NULL, 0) < 0) {
                printf("Worker: Waitpid failed!\n");
                exit(ERROR);
            }

            char outputFileName[OUTPUT_FILE_NAME_MAX_LENGTH];
            sprintf(outputFileName, "%s.output", job->jobID);

            char info[INFO_LENGTH];
            char outputStart[strlen("-----jobID  output start-----\n") + strlen("Job_XX")];
            char outputEnd[strlen("-----jobID  output end-----\n") + strlen("Job_XX")];
            sprintf(outputStart, "-----jobID %s output start------\n", job->jobID);
            sprintf(outputEnd, "-----jobID %s output end------\n", job->jobID);

            send(job->clientSocket, outputStart, strlen(outputStart), 0);

            FILE *fp = fopen(outputFileName, "r");
            if (fp == NULL) {
                pthread_mutex_lock(&concurrencyMutex);
                runningJobs--;
                pthread_cond_signal(&concurrencyCond);
                pthread_mutex_unlock(&concurrencyMutex);
                continue;
            }

            while (fgets(info, sizeof(info), fp) != NULL)
                send(job->clientSocket, info, strlen(info), 0);

            send(job->clientSocket, outputEnd, strlen(outputEnd), 0);

            fclose(fp);
            
            remove(outputFileName);

            close(job->clientSocket);

            free(job->job);
            free(job);

            pthread_mutex_lock(&concurrencyMutex);
            runningJobs--;
            pthread_cond_signal(&concurrencyCond);
            pthread_mutex_unlock(&concurrencyMutex);
        }
    }
    
    return 0;
}
