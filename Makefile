CC = gcc
OBJECTS = main.o libCPU_CACHE.c
TOBJECTS = testCPU_CACHE.o libCPU_CACHE.o
TOBJECTS2 = testCPU_Idle_Read.o libCPU_CACHE.o libCPU_Idle_Read.o
LFLAGS = -O2 -Wall -lpthread
CFLAGS = -Iinclude
EXE = main0.0.1


$(EXE): $(OBJECTS)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

test: $(TOBJECTS)
	$(CC) $(CFLAGS) -o test $(TOBJECTS) $(LFLAGS)

test2: $(TOBJECTS2)
	$(CC) $(CFLAGS) -o test2 $(TOBJECTS2) $(LFLAGS)

testCPU_CACHE.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_CACHE.c -o testCPU_CACHE.o $(LFLAGS)

testCPU_Idle_Read.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_Idle_Read.c -o testCPU_Idle_Read.o $(LFLAGS)

libCPU_CACHE.o:
	$(CC) $(CFLAGS) -c source/libCPU_CACHE.c -o libCPU_CACHE.o $(LFLAGS)

libCPU_Idle_Read.o:
	$(CC) $(CFLAGS) -c source/libCPU_Idle_Read.c -o libCPU_Idle_Read.o $(LFLAGS)

clean:
	rm -rf $(EXE) test test2 *.o