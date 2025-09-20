#include "./include/jobCommander.h"

// Handler for pipes
void pipe_sig_handler(int signum) {
}

int main(int argc, char *argv[]) {

    // Check proper function call
    if (argv_check(argc, argv)) {
        printf("Commander: Wrong or not enough arguments!\n");
        exit(ERROR);
    }

    // Setup handler for pipes
    struct sigaction pipe_sa;
    pipe_sa.sa_handler = pipe_sig_handler;
    pipe_sa.sa_flags = SA_RESTART;
    if (sigaction(SIGUSR1, &pipe_sa, NULL) == -1) {
        perror("Commander: Error setting up pipes handler");
        exit(ERROR);
    }

    // Check if server is running and start it if not
    struct stat buffer;
    pid_t pid;
    bool wasRunning = false; // server was/was not already running
    int fd;

    // Server already running ==> get pid of server
    if (stat(TXT, &buffer) == 0) {
        if ((fd = open(TXT, O_RDONLY)) == -1) {
            perror("Commander: Can't open txt file");
            exit(ERROR);
        }
        if (read(fd, &pid, sizeof(pid)) == -1) {
            perror("Commander: Can't read pid from txt file");
            exit(ERROR);
        }
        wasRunning = true;
    }
    // Server not already running ==> start it
    else {
        // Find the path
        char *dir = dirname(argv[0]);
        char path[100];
        snprintf(path, sizeof(path), "%s/jobExecutorServer", dir);
        if ((pid = fork()) < 0) {
            perror("Commander: Forked failed");
            exit(ERROR);
        }
        // Child becomes server
        if (pid == 0) {
            execlp(path, path, NULL);
            perror("Commander: Failed to start server");
            exit(ERROR);
        }
        // Parent becomes commander and waits for server to create the pipes
        else {
            pause();
        }
    }

    // Open pipes for writing and reading
    int command_pipe;
    if ((command_pipe = open(COMMAND_PIPE, O_WRONLY)) == -1) {
        perror("Commander: Can't open command pipe");
        exit(ERROR);
    }

    int info_pipe;
    if ((info_pipe = open(INFO_PIPE, O_RDONLY)) == -1) {
        perror("Commander: Can't open info pipe");
        exit(ERROR);
    }

    // Send the command to the server
    int command_size = 0;
    for (int i = 1; i < argc; i++)
        command_size += strlen(argv[i]);
    command_size += argc; // size for spaces and null terminator
    char command[command_size];
    command[0] = '\0';
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    // Send command_size, argc and command 
    if (write(command_pipe, &command_size, sizeof(command_size)) == -1) {
        perror("Commander: Can't send command size");
        exit(ERROR);
    }
    if (write(command_pipe, &argc, sizeof(argc)) == -1) {
        perror("Commander: Can't send argc");
        exit(ERROR);
    }
    if (write(command_pipe, command, command_size) == -1) {
        perror("Commander: Can't send command");
        exit(ERROR);
    }

    // Signal the server that a command was sent
    kill(pid, SIGUSR1);

    // Receive the info from the server(if necessary) depending on the command
    if (!strcmp(argv[1], "issueJob")) {
        int info_size;
        if (read(info_pipe, &info_size, sizeof(info_size)) == -1) {
            perror("Commander: Can't receive issueJob info size");
            exit(ERROR);
        }
        char info[info_size];
        if (read(info_pipe, info, info_size) == -1) {
            perror("Commander: Can't receive issueJob info");
            exit(ERROR);
        }
        printf("%s\n", info);
    }
    else if (!strcmp(argv[1], "stop")) {
        // maximum length possible based on the expected info
        char info[23];
        if (read(info_pipe, info, sizeof(info)) == -1) {
            perror("Commander: Can't receive stop info");
            exit(ERROR);
        }
        printf("%s\n", info);
    }
    else if (!strcmp(argv[1], "poll")) {
        int queue_size;
        if (read(info_pipe, &queue_size, sizeof(queue_size)) == -1) {
            perror("Commander: Can't receive queue size");
            exit(ERROR);
        }
        for (int i = 0; i < queue_size; i++) {
            int info_size;
            if (read(info_pipe, &info_size, sizeof(info_size)) == -1) {
                perror("Commander: Can't receive poll info size");
                exit(ERROR);
            }
            char info[info_size];
            if (read(info_pipe, info, info_size + 1) == -1) {
                perror("Commander: Can't receive poll info");
                exit(ERROR);
            }
            printf("%s\n", info);
        }
    }
    else if (!strcmp(argv[1], "exit")) {
        int info_size = strlen("jobExecutorServer terminated") + 1; 
        char info[info_size];
        if (read(info_pipe, info, info_size) == -1) {
            perror("Commander: Can't receive exit info");
            exit(ERROR);
        }
        printf("%s\n", info);
    }

    // Closing

    // Close file in case we opened it
    if (wasRunning) {
        if (close(fd) == -1) {
            perror("Commander: Can't close txt file");
            exit(ERROR);
        }
    }

    // Closing command, info pipes and semaphores
    if (close(command_pipe) == -1) {
        perror("Commander: Can't close command pipe");
        exit(ERROR);
    }

    if (close(info_pipe) == -1) {
        perror("Commander: Can't close info pipe");
        exit(ERROR);
    }

    return 0;
}

int argv_check(int argc, char *argv[]) {
    if (argc == 1)
        return 1;

    if (!strcmp(argv[1], "issueJob") && argc > 2)
        return 0;

    if (!strcmp(argv[1], "setConcurrency") && argc == 3 && isdigit(*argv[2]))
        return 0;

    if (!strcmp(argv[1], "stop") && argc == 3 && job_check(argv[2]))
        return 0;

    if (!strcmp(argv[1], "poll") && argc == 3 && (!strcmp(argv[2], "running") || !strcmp(argv[2], "queued")))
        return 0;

    if (!strcmp(argv[1], "exit") && argc == 2)
        return 0;

    return 1;
}

bool job_check(char *job) {
    if (strncmp(job, "job_", 4) != 0)
        return false;

    if (job[4] == '\0')
        return false; 

    for (int i = 4; job[i] != '\0'; i++)
        if (!isdigit(job[i]))
            return false;

    return true;
}