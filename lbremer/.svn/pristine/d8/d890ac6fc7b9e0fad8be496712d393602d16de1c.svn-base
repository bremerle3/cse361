all:  lab0

clean:
	rm -f lab0 *.o

input.o:  input.c
	gcc -m32 -g -c input.c -o input.o

lab0.o:  lab0.c input.h
	gcc -m32 -g -c lab0.c -o lab0.o

lab0:  lab0.o input.o
	gcc -m32 -g lab0.o input.o -o lab0
