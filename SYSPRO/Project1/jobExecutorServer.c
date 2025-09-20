#include "include/jobExecutorServer.h"

// Handler for command
void command_sig_handler(int signum) { 
}

// Handler for job termination
void job_sig_handler(int signum) {
}

int main(void) {
    
    // Setup handler for command
    struct sigaction command_sa;
    command_sa.sa_handler = command_sig_handler;
    command_sa.sa_flags = SA_RESTART;
    if (sigaction(SIGUSR1, &command_sa, NULL) == -1) {
        perror("Server: Error setting up command handler");
        exit(ERROR);
    }

    // Setup handler for job termination
    struct sigaction job_sa;
    job_sa.sa_handler = job_sig_handler;
    job_sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &job_sa, NULL) == -1) {
        perror("Server: Error setting up job termination handler");
        exit(ERROR);
    }

    // Create struct to monitor jobs
    struct Jobs jobs;

    jobs.concurrency = 1;
    jobs.ids = 0;
    jobs.queuedJobs = createQueue();
    jobs.runningJobs = createQueue();

    // Start server
    int fd, command_pipe, info_pipe;
    if (starting(&fd, &command_pipe, &info_pipe)) {
        printf("Server: Can't start!\n");
        exit(ERROR);
    }

    // Main loop, which stops only when server terminates
    while (1) {
        // Server idle until command arrives or job finishes/stops
        pause();
        // while commands exist => read them => add jobs to queue
        // break when all commands are read
        while (1) {
            int command_size;
            int bytes;
            if ((bytes = read(command_pipe, &command_size, sizeof(command_size))) == -1)
                break;
            int argc;
            if ((bytes = read(command_pipe, &argc, sizeof(argc))) == -1)
                break;
            argc -= 1;
            char command[command_size];
            if ((bytes = read(command_pipe, command, command_size)) == -1)
                break;
            if (bytes == 0)
                break;

            // Split command and arguments
            char *argument = strtok(command, " ");

            // Check first argument, which is the command

            // issueJob
            if (!strcmp(argument, "issueJob")) {
                // Create new job
                struct Job *job = (struct Job *)malloc(sizeof(struct Job));
                if (job == NULL) {
                    perror("Server: Malloc failed for struct job");
                    exit(ERROR);
                }

                // jobID
                job->jobID = malloc(7);
                if (job->jobID == NULL) {
                    perror("Server: Malloc failed for jobID");
                    exit(ERROR);
                }
                strcpy(job->jobID, "job_");
                job->jobID[4] = '\0';
                char id[3];
                snprintf(id, sizeof(id), "%d", ++(jobs.ids));
                strcat(job->jobID, id);

                // queuePosition
                job->queuePosition = jobs.queuedJobs->size + 1;

                // job
                job->job = (char **)malloc(sizeof(char *) * argc);
                if (job->job == NULL) {
                    perror("Server: Malloc failed for job");
                    exit(ERROR);
                }
                char command_cpy[command_size - strlen("issueJob")];
                command_cpy[0] = '\0';
                int i = 0;
                do {
                    argument = strtok(NULL, " ");
                    if (argument != NULL) {
                        job->job[i] = malloc(strlen(argument) + 1); // Allocate memory for each argument
                        if (job->job[i] == NULL) {
                            perror("Server: Malloc failed for job argument");
                            exit(ERROR);
                        }
                        strcpy(job->job[i], argument);
                        strcat(command_cpy, job->job[i]);
                        strcat(command_cpy, " ");
                        i++;
                    }
                } while (argument != NULL);
                job->job[i] = NULL;
                // remove last ' '
                if (command_cpy[strlen(command_cpy) - 1] == ' ')
                    command_cpy[strlen(command_cpy) - 1] = '\0';
               
                // info
                char pos[3];
                snprintf(pos, sizeof(pos), "%d", job->queuePosition);

                int info_size = strlen(command_cpy) + strlen(job->jobID) + strlen(pos) + 6;

                char info[info_size];
                info[0] = '\0';
                strcat(info, "<");
                strcat(info, job->jobID);
                strcat(info, ",");
                strcat(info, command_cpy);
                strcat(info, ",");
                strcat(info, pos);
                strcat(info, ">");

                job->info = malloc(sizeof(char)*info_size);
                strcpy(job->info, info);

                // pid(initially -1)
                job->pid = -1;

                // Add job to queue
                push(jobs.queuedJobs, job);

                // Send job info to commander
                if (write(info_pipe, &info_size, sizeof(info_size)) == -1) {
                    perror("Server: Can't write info size");
                    exit(ERROR);
                }

                if (write(info_pipe, info, info_size) == -1) {
                    perror("Server: Can't write info ");
                    exit(ERROR);
                }
            }

            // setConcurrency
            else if (!strcmp(argument, "setConcurrency")) {
                argument = strtok(NULL, " ");
                jobs.concurrency = atoi(argument);
            }

            // stop
            else if (!strcmp(argument, "stop")) {
                // remove the job from whichever queue it belongs to and kill it if it was running
                // also free its memory
                struct Job *job;
                argument = strtok(NULL, " ");
                int exists = 0;

                if ((job = popID(jobs.queuedJobs, argument)) != NULL) {
                    exists = 1;
                    freeJob(job);
                }
                else if ((job = popID(jobs.runningJobs, argument)) != NULL) {
                    exists = 2;
                    kill(job->pid, SIGKILL);
                    freeJob(job);
                }

                // maximum possible length needed
                char info[strlen(argument) + 16];
                info[0] = '\0';
                strcat(info, argument);
                strcat(info, " ");

                switch (exists)
                {
                case 0:
                    strcat(info, "does not exist");
                    break;
                case 1:
                    strcat(info, "removed");
                    break;
                case 2:
                    strcat(info, "terminated");
                    break;
                }

                if (write(info_pipe, info, strlen(info) + 1) == -1) {
                    perror("Server: Can't write info size");
                    exit(ERROR);
                }
            }

            // poll
            else if (!strcmp(argument, "poll")) {
                argument = strtok(NULL, " ");
                struct Queue *queue;

                if (!strcmp(argument, "running"))
                    queue = jobs.runningJobs;
                else if (!strcmp(argument, "queued"))
                    queue = jobs.queuedJobs;

                if (write(info_pipe, &queue->size, sizeof(queue->size)) == -1) {
                    perror("Server: Can't write queue size");
                    exit(ERROR);
                }

                for (int i = 0; i < queue->size; i++) {
                    struct Job *job = getJob(queue, i);
                    int info_size = strlen(job->info);

                    if (write(info_pipe, &info_size, sizeof(info_size)) == -1) {
                        perror("Server: Can't write queue info size");
                        exit(ERROR);
                    }

                    if (write(info_pipe, job->info, info_size + 1) == -1) {
                        perror("Server: Can't write queue info");
                        exit(ERROR);
                    }
                }
            }

            // exit
            else if (!strcmp(argument, "exit")) {

                if (write(info_pipe, "jobExecutorServer terminated", strlen("jobExecutorServer terminated") + 1) == -1) {
                    perror("Server: Can't write queuedJobs size");
                    exit(ERROR);
                }

                if (closing(fd, command_pipe, info_pipe)) {
                    printf("Server: Can't close!\n");
                    exit(ERROR);
                }

                kill(getpid(), SIGTERM);
            }
        }


        // pick up finished or killed jobs, remove them from running queue and free the memory
        int job_pid;
        int status;
        while ((job_pid = waitpid(-1, &status, WNOHANG)) > 0)
            free(popPID(jobs.runningJobs, job_pid));

        // run as many jobs possible
        while (jobs.runningJobs->size < jobs.concurrency) {
            struct Job *job = pop(jobs.queuedJobs);

            // no jobs queued
            if (job == NULL) {
                break;
            }
            // run next job
            else {
                pid_t pid = fork();
                if (pid == -1) {
                    perror("Server: Fork failed");
                    exit(ERROR);
                }
                // Child process ==> run job
                else if (pid == 0) {
                    execvp(job->job[0], job->job);
                    perror("Server: Exec failed");
                    exit(ERROR);
                }
                // Server process ==> add job to running queue
                else {
                    job->pid = pid;
                    push(jobs.runningJobs, job);
                }
            }
        }
    }
    return 0;
}

int closing(int fd, int command_pipe, int info_pipe) {

    // Closing and deleting jobExecutorServer.txt
    if (close(fd) == -1) {
        perror("Server: Can't close txt");
        exit(ERROR);
    }

    if (unlink(TXT) == -1) {
        perror("Server: Can't unlink txt");
        exit(ERROR);
    }

    // Closing and deleting command and info pipes
    if (close(command_pipe) == -1) {
        perror("Server: Can't close command pipe");
        exit(ERROR);
    }

    if (unlink(COMMAND_PIPE) == -1) {
        perror("Server: Can't delete command pipe");
        exit(ERROR);
    }

    if (close(info_pipe) == -1) {
        perror("Server: Can't close info pipe");
        exit(ERROR);
    }

    if (unlink(INFO_PIPE) == -1) {
        perror("Server: Can't delete info pipe");
        exit(ERROR);
    }

    return 0;
}

int starting(int *fd, int *command_pipe, int *info_pipe) {

    // Create jobExecutorServer.txt and write pid
    if ((*fd = open(TXT, O_RDWR | O_CREAT | O_EXCL, TXT_PERMS)) == -1) {
        perror("Server: Can't create txt");
        exit(ERROR);
    }

    pid_t pid = getpid();

    if (write(*fd, &pid, sizeof(pid)) == -1) {
        perror("Server: Can't write pid");
        exit(ERROR);
    }

    // Create and open command and info pipes
    if ((mkfifo(COMMAND_PIPE, PIPE_PERMS) < 0) && (errno != EEXIST)) {
        perror("Server: Can't create command pipe");
        exit(ERROR);
    }

    if ((mkfifo(INFO_PIPE, PIPE_PERMS) < 0) && (errno != EEXIST)) {
        perror("Server: Can't create info pipe");
        exit(ERROR);
    }

    // Signal the commander that the pipes have been created
    kill(getppid(), SIGUSR1);

    if ((*command_pipe = open(COMMAND_PIPE, O_RDONLY | O_NONBLOCK)) == -1) {
        perror("Server: Can't open command pipe");
        exit(ERROR);
    }

    if ((*info_pipe = open(INFO_PIPE, O_WRONLY)) == -1) {
        perror("Server: Can't open info pipe");
        exit(ERROR);
    }

    return 0;
}

void freeJob(struct Job *job) {
    free(job->info);
    free(job->jobID);
    for (int i = 0; job->job[i] != NULL; i++)
        free(job->job[i]);
    free(job->job);
}