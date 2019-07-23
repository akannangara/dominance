CC=g++
CFLAGS=-O3 -Wall -std=c++11 -fopenmp

main: main.cpp
	$(CC) -o dominance2 main.cpp manager.cpp player.cpp statistics.cpp $(CFLAGS)
