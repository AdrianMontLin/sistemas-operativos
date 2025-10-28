CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2

all: main suma1 suma2 sumatotal

main: main.c leer.o
	$(CC) $(CFLAGS) -o main main.c leer.o

suma1: suma1.c leer.o
	$(CC) $(CFLAGS) -o suma1 suma1.c leer.o

suma2: suma2.c leer.o
	$(CC) $(CFLAGS) -o suma2 suma2.c leer.o

sumatotal: sumatotal.c leer.o
	$(CC) $(CFLAGS) -o sumatotal sumatotal.c leer.o

leer.o: leer.c leer.h
	$(CC) $(CFLAGS) -c leer.c

clean:
	rm -f *.o main suma1 suma2 sumatotal
.PHONY: all clean
