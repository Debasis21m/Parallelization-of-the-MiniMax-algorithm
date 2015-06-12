all: main

main: main.o board.o
	gcc -o main.exe main.o board.o -lpthread

main.o: main.c board.h
	gcc -o main.o -c main.c -lpthread

board.o: board.c board.h
	gcc -o board.o -c board.c

clean:
	rm -f board.o main.o main.exe

run:
	qsub -q ibm-nehalem.q -cwd ./run.sh $(N)
