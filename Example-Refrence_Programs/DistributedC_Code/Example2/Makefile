# have to call make librarytest to run it.
CC=gcc
CFLAGS= -Wall -g
BINS=librarytest libmycode.so runtime_librarytest

all: $(BINS)

$(EXE): $(OBJECTS)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS)

libmycode.o: libmycode.c mycode.h
	$(CC) $(CFLAGS) -c libmycode.c

libmycode.so: libmycode.c mycode.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ libmycode.c -lc
# This is designed to be loaded at runtime.
# -fPIC = Position-Independent Code

librarytest: librarytest.c libmycode.o
	$(CC) $(CFLAGS) -o $@ $^

runtime_librarytest: librarytest.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmycode
# -L. = `look in current directory for librarys.`
# -lmycode = `link the program with libmycode
# the dash l (-l) is shorthand to look for lib...




clean:
	rm *.o *.so $(BINS)