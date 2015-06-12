all: main

main: main.o board.o
	mpicc -o main.exe main.o board.o

main.o: main.c board.h
	mpicc -o main.o -c main.c

board.o: board.c board.h
	mpicc -o board.o -c board.c

clean:
	rm -f board.o main.o main.exe

run:
	qsub -q ibm-nehalem.q -pe openmpi 5 -cwd ./run.sh 5
