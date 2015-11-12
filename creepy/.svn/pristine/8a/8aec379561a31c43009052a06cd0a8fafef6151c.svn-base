CC = gcc
CFLAGS = -m32 -pg -O3

all:  hist

clean:
	rm -f hist *.o

hist:  hist.c student.h input.h yourcode.c
	gcc $(CFLAGS) yourcode.c hist.c -o hist
