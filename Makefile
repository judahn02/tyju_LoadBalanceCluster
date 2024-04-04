CC = gcc
OBJECTS = main.o libCPU_CACHE.c
TOBJECTS = testCPU_CACHE.o libCPU_CACHE.o
LFLAGS = -O2 -Wall -std=c++11
CFLAGS = -Iinclude
EXE = main0.0.1



$(EXE): $(OBJECTS)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

test: $(TOBJECTS)
	$(CC) $(CFLAGS) -o test $(TOBJECTS) $(LFLAGS)

testCPU_CACHE.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_CACHE.c -o testCPU_CACHE.o

libCPU_CACHE.o:
	$(CC) $(CFLAGS) -c source/libCPU_CACHE.c -o libCPU_CACHE.o

clean:
	rm -rf $(EXE) test *.o