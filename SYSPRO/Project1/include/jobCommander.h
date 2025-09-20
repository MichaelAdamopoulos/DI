#define _DEFAULT_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE_PERMS 0666
#define TXT_PERMS 0644
#define TXT "jobExecutorServer.txt"
#define COMMAND_PIPE "./command"
#define INFO_PIPE "./info"
#define ERROR -1

// Function to check if arguments are correct
int argv_check(int, char **);

// Function to check if a job is of type job_XX
bool job_check(char *);