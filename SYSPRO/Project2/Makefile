all: jobCommander jobExecutorServer

jobCommander: jobCommander.c
	gcc -o jobCommander jobCommander.c

jobExecutorServer: jobExecutorServer.c
	gcc -o jobExecutorServer jobExecutorServer.c -pthread

clean:
	rm -f jobCommander jobExecutorServer
	clear