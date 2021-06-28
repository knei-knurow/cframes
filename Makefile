ROOT := ${CURDIR}

CC := gcc
CFLAGS := -std=c11 -Wall
INCLUDES := -I$(ROOT)

all: example.o frames.o
	$(CC) $(CFLAGS) -o example example.o frames.o

example.o: example.c
	$(CC) $(CFLAGS) -c example.c $(INCLUDES)

frames.o: frames.c
	$(CC) $(CFLAGS) -c frames.c $(INCLUDES)

clean:
	rm -f example *.o
