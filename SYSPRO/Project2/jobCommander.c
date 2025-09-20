#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

#define INFO_BUFFER_SIZE 1024       // for reading data from controllers

#define ERROR -1

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Commander: Not enough arguments!\n");
        exit(ERROR);
    }

    char *serverName = argv[1];
    int portNum = atoi(argv[2]);
    char *command = argv[3];

    // Extract the full command
    int commandLength = 0;
    for (int i = 3; i < argc; i++)
        commandLength += strlen(argv[i]) + 1; // +1 for space or '\0'

    char *fullCommand = (char *)malloc(commandLength);
    if (fullCommand == NULL) {
        printf("Commander: Malloc for fullCommand failed!\n");
        exit(ERROR);
    }

    fullCommand[0] = '\0';
    for (int i = 3; i < argc; i++) {
        strcat(fullCommand, argv[i]);
        if (i != argc - 1)
            strcat(fullCommand, " ");
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Commander: Socket creation failed!\n");
        exit(ERROR);
    }

    // Get server address
    struct hostent *host = gethostbyname(serverName);
    if (host == NULL) {
        printf("Commander: Getting host failed!\n");
        close(sock);
        exit(ERROR);
    }

    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr *)&server;
    server.sin_family = AF_INET;
    memcpy(&server.sin_addr, host->h_addr, host->h_length);
    server.sin_port = htons(portNum);

    // Connect to the server
    if (connect(sock, serverptr, sizeof(server)) < 0) {
        printf("Commander: Connection to server failed!\n");
        close(sock);
        exit(ERROR);
    }

    // Write the command (first the length and then the command itself)
    commandLength = htonl(strlen(fullCommand));

    if (write(sock, &commandLength, sizeof(commandLength)) < 0) {
        printf("Commander: Writing command length failed!\n");
        close(sock);
        exit(ERROR);
    }

    if (write(sock, fullCommand, strlen(fullCommand)) < 0) {
        printf("Commander: Writing command failed!\n");
        close(sock);
        exit(ERROR);
    }

    // Read the info
    char info[INFO_BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = read(sock, info, sizeof(info) - 1)) > 0) {
        info[bytesRead] = '\0';
        printf("%s", info);
    }

    if (bytesRead < 0)
        printf("Commander: Reading info failed!\n");

    // Finish up
    free(fullCommand);
    close(sock);

    return 0;
}