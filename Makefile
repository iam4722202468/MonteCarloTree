CC=g++

generate: main.o mcr.o
				$(CC) -o generate main.o mcr.o -fopenmp

main.o: main.cpp mcr.h
				$(CC) -c main.cpp
mcr.o: mcr.cpp mcr.h
				$(CC) -c mcr.cpp -fopenmp
clean:
				rm generate main.o mcr.o

