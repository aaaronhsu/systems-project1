all: main.o
	gcc -o p1 main.c

main.o: main.c
	gcc -c main.c

run:
	./p1