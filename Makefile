ROOT := ${CURDIR}

CC := gcc
CFLAGS := -std=c11 -Wall

all: example.o frames.o
	$(CC) $(CFLAGS) -o example example.o frames.o

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

frames.o: frames.c
	$(CC) $(CFLAGS) -c frames.c

clean:
	rm -f example *.o
