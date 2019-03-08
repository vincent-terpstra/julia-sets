#Makefile for w1
#
GCC_VERSION = 8.2.0
PREFIX = /usr/local/gcc/${GCC_VERSION}/bin/
CC = ${PREFIX}gcc
CPP = ${PREFIX}g++

julia : julia.o
	$(CPP) -pg -ojulia julia.o Bitmap.cpp

julia.o: julia.cpp
	$(CPP) -c -O2 -g -pg -std=c++17 julia.cpp

clean:
	rm *.o
