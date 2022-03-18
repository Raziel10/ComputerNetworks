LIB_PATH = ./lib

all:
	g++ -I ${LIB_PATH} -c ${LIB_PATH}/ALOHA.cpp
	g++ -I ${LIB_PATH} -c ${LIB_PATH}/simulator.cpp
	g++ -I ${LIB_PATH} -c main.cpp
	g++ main.o simulator.o aloha.o -o main.out
