CC = gcc
CFLAGS = -m32 -O0

all:  hist

clean:
	rm -f hist *.o

hist:  hist.c student.h input.h yourcode.h
	gcc $(CFLAGS) yourcode.c hist.c -o hist
