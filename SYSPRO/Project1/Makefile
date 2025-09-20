OBJS_COMMANDER = jobCommander.o queue.o
OBJS_EXECUTOR = jobExecutorServer.o queue.o
SOURCE_COMMANDER = jobCommander.c queue.c
SOURCE_EXECUTOR = jobExecutorServer.c queue.c
HEADER = jobCommander.h jobExecutorServer.h queue.h common_types.h
OUT_COMMANDER = jobCommander
OUT_EXECUTOR = jobExecutorServer
CC = gcc
FLAGS = -g -c -pthread

all: $(OUT_COMMANDER) $(OUT_EXECUTOR)
 
$(OUT_COMMANDER): $(OBJS_COMMANDER)
	$(CC) -g $(OBJS_COMMANDER) -o $(OUT_COMMANDER) -pthread

$(OUT_EXECUTOR): $(OBJS_EXECUTOR)
	$(CC) -g $(OBJS_EXECUTOR) -o $(OUT_EXECUTOR) -pthread

jobCommander.o: jobCommander.c
	$(CC) $(FLAGS) jobCommander.c -o jobCommander.o

jobExecutorServer.o: jobExecutorServer.c
	$(CC) $(FLAGS) jobExecutorServer.c -o jobExecutorServer.o

queue.o: queue.c include/queue.h
	$(CC) $(FLAGS) queue.c -o queue.o

clean:
	rm -f $(OBJS_COMMANDER) $(OUT_COMMANDER) $(OBJS_EXECUTOR) $(OUT_EXECUTOR)
	clear