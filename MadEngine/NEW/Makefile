FILENAME=test.cpp
OUTNAME=MadEngine
CC=g++
LFLAGS=-lglut -lglfw -framework OpenGL
CFLAGS=-std=c++11
SRC=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(FILENAME)
BIN=./bin

compile:
	g++ $(SRC) $(CFLAGS) -o $(BIN)/$(OUTNAME) $(LFLAGS)

compile.run:
	g++ $(SRC) $(CFLAGS) -o $(BIN)/$(OUTNAME) $(LFLAGS)
	$(BIN)/$(OUTNAME)