CC=gcc
CFLAGS=-I.
DEPS = matrixMultiply.h hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

20050111076: 20050111076.o matrixMultiply.o hellofunc.o
	$(CC) -o 20050111076 20050111076.o matrixMultiply.o hellofunc.o
