all: main.o functions.o
	gcc -o p1 main.c functions.c

main.o: main.c functions.h
	gcc -c main.c

functions.o: functions.c functions.h
	gcc -c functions.c

run:
	./p1

lol:
	git add .
	git commit -m "running on school computer"
	git push