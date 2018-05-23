CC=gcc
CFLAGS=-I.

mutex_1_way : 
	$(CC) -o mutex_1_way mutex.c -pthread $(CFLAGS)

mutex_2_way : 
	$(CC) -o mutex_2_way mutex.c -pthread $(CFLAGS)

factorial : 
	$(CC) -o factorial factorial.c -pthread $(CFLAGS)

deadlock : 
	$(CC) -o deadlock deadlock.c -pthread $(CFLAGS)

clean :
	rm mutex_1_way mutex_2_way factorial deadlock

all : deadlock mutex_1_way mutex_2_way factorial
    