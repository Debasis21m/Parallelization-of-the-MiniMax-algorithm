all: main

main: main.o board.o
	gcc -o main.exe main.o board.o -fopenmp

main.o: main.c board.h
	gcc -o main.o -c main.c -fopenmp

board.o: board.c board.h
	gcc -o board.o -c board.c

clean:
	rm -f board.o main.o main.exe

run:
	qsub -q ibm-nehalem.q -cwd -pe openmp 16 ./run.sh 16
