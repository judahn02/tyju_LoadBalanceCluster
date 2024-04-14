CC = mpicc
OBJECTS = main.o libCPU_CACHE.o libCPU_Idle_Read.o libstress.o libRAM_read.o\
			libCPU_speed_CoreCt.o libcontrol.o libworker.o libtableManage.o\
			libsharedFunctions.o

TOBJECTS = testCPU_CACHE.o libCPU_CACHE.o
TOBJECTS2 = testCPU_Idle_Read.o libCPU_CACHE.o libCPU_Idle_Read.o
TOBJECTS3 = teststress.o libstress.o
TOBJECTS4 = testRAM_read.o libRAM_read.o
LFLAGS = -Wall -Wextra -lpthread -lm 
CFLAGS = -Iinclude
EXE = main


$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o $(LFLAGS)

test: $(TOBJECTS)
	$(CC) $(CFLAGS) -o test $(TOBJECTS) $(LFLAGS)

test2: $(TOBJECTS2)
	$(CC) $(CFLAGS) -o test2 $(TOBJECTS2) $(LFLAGS)

test3: $(TOBJECTS3)
	$(CC) $(CFLAGS) -o test3 $(TOBJECTS3) $(LFLAGS)

test4: $(TOBJECTS4)
	$(CC) $(CFLAGS) -o test4 $(TOBJECTS4) $(LFLAGS)

testCPU_CACHE.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_CACHE.c -o testCPU_CACHE.o $(LFLAGS)

testCPU_Idle_Read.o: 
	$(CC) $(CFLAGS) -c tests/testCPU_Idle_Read.c -o testCPU_Idle_Read.o $(LFLAGS)

teststress.o:
	$(CC) $(CFLAGS) -c tests/teststress.c -o teststress.o $(LFLAGS)

testRAM_read.o:
	$(CC) $(CFLAGS) -c tests/testRAM_read.c -o testRAM_read.o $(LFLAGS)

libCPU_CACHE.o:
	$(CC) $(CFLAGS) -c source/libCPU_CACHE.c -o libCPU_CACHE.o $(LFLAGS)

libCPU_Idle_Read.o:
	$(CC) $(CFLAGS) -c source/libCPU_Idle_Read.c -o libCPU_Idle_Read.o $(LFLAGS)

libstress.o:
	$(CC) $(CFLAGS) -c source/libstress.c -o libstress.o $(LFLAGS)

libRAM_read.o:
	$(CC) $(CFLAGS) -c source/libRAM_read.c -o libRAM_read.o $(LFLAGS)

libCPU_speed_CoreCt.o:
	$(CC) $(CFLAGS) -c source/libCPU_speed_CoreCt.c -o libCPU_speed_CoreCt.o $(LFLAGS)

libcontrol.o:
	$(CC) $(CFLAGS) -c source/libcontrol.c -o libcontrol.o $(LFLAGS)

libworker.o:
	$(CC) $(CFLAGS) -c source/libworker.c -o libworker.o $(LFLAGS)

libtableManage.o:
	$(CC) $(CFLAGS) -c source/libtableManage.c -o libtableManage.o $(LFLAGS)

libsharedFunctions.o:
	$(CC) $(CFLAGS) -c source/libsharedFunctions.c -o libsharedFunctions.o $(LFLAGS) 

install: $(EXE)
	rm -rf $(OBJECTS)

clean:
	rm -rf $(EXE) test test1 test2 test3 test4 *.o