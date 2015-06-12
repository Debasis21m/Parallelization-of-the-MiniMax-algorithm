# Parallelization of the MixiMax algorithm

The project contains 4 MiniMax implementations for the Tic Tac Toe game:
- secvential version
- parallel version, using OpenMP
- parallel version, using MPI
- parallel version, using POSIX pthreads library

## Results obtained with the 4x4 dimension of the game:

Secvential version:
	- 2m36.673s

OpenMP:
	- 4 threads: 0m44.251s
	- 8 threads: 0m42.918s

MPI:
	- 4 processes: 0m42.311s
	- 8 proecesses: 0m43.298s

pthreads:
	- 4 threads: 0m49.723s
	- 8 threads: 0m40.227s
