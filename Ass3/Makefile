.PHONY:life enter_the_matrix

sieve_omp: sieve_omp.cpp
	g++ -std=c++11 -Wall -g -fopenmp -pthread sieve_omp.cpp -o sieve 

life: Game_Of_Life.c
	gcc -Wall -g -fopenmp -pthread Game_Of_Life.c -o life 
enter_the_matrix: matrix.cpp
	g++ -std=c++11 -Wall -g -fopenmp -pthread matrix.cpp -o matrix
gauss: Gauss.cpp
	g++ -std=c++11 -Wall -g -fopenmp -pthread Gauss.cpp -o gauss
	