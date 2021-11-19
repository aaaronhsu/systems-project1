all: main.o
	gcc -o p1 main.c

main.o: main.c headers.h
	gcc -c main.c

run:
	./p1