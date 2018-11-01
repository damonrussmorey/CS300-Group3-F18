FLAGS=-g -Wall
LIB=-pthread
CC=g++
INC=-I include

SOURCES=$(shell find src -type f -name *.cpp)

all: bin/ProviderTerminal bin/ManagerTerminal bin/UnitTests

clean:
	rm -f build/* bin/*

bin/ProviderTerminal: build/ProviderTerminal.o build/DataCenter.o
	$(CC) $(LIB) -o bin/ProviderTerminal build/ProviderTerminal.o build/DataCenter.o

bin/ManagerTerminal: build/ManagerTerminal.o build/DataCenter.o
	$(CC) $(LIB) -o bin/ManagerTerminal build/ManagerTerminal.o build/DataCenter.o

bin/UnitTests: build/*Test.o
	$(CC) $(LIB) -o bin/UnitTests build/*Test.o

build/%.o: src/%.cpp
	@mkdir -p build
	$(CC) $(FLAGS) $(INC) -c -o $@ $<
