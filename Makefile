CC = gcc
OBJECTS = main.o libCPU_CACHE.o libCPU_Idle_Read.o libstress.o
TOBJECTS = testCPU_CACHE.o libCPU_CACHE.o
TOBJECTS2 = testCPU_Idle_Read.o libCPU_CACHE.o libCPU_Idle_Read.o
TOBJECTS3 = teststress.o libstress.o
LFLAGS = -O2 -Wall -lpthread
CFLAGS = -Iinclude
EXE = main0.0.1


$(EXE): $(OBJECTS)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

test: $(TOBJECTS)
	$(CC) $(CFLAGS) -o test $(TOBJECTS) $(LFLAGS)

test2: $(TOBJECTS2)
	$(CC) $(CFLAGS) -o test2 $(TOBJECTS2) $(LFLAGS)

test3: $(TOBJECTS3)
	$(CC) $(CFLAGS) -o test3 $(TOBJECTS3) $(LFLAGS)

testCPU_CACHE.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_CACHE.c -o testCPU_CACHE.o $(LFLAGS)

testCPU_Idle_Read.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_Idle_Read.c -o testCPU_Idle_Read.o $(LFLAGS)

teststress.o:
	$(CC) $(CFLAGS) -c tests/teststress.c -o teststress.o $(LFLAGS)

libCPU_CACHE.o:
	$(CC) $(CFLAGS) -c source/libCPU_CACHE.c -o libCPU_CACHE.o $(LFLAGS)

libCPU_Idle_Read.o:
	$(CC) $(CFLAGS) -c source/libCPU_Idle_Read.c -o libCPU_Idle_Read.o $(LFLAGS)

libstress.o:
	$(CC) $(CFLAGS) -c source/libstress.c -o libstress.o $(LFLAGS)


clean:
	rm -rf $(EXE) test test2 test3 *.o