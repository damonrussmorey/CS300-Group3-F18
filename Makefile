FLAGS=-g -Wall
LIB=-pthread
CC=g++
INC=-I include

SOURCES=$(shell find src -type f -name *.cpp)

all: bin/Test

clean:
	rm -f build/* bin/*

bin/ProviderTerminal: build/ProviderTerminal.o build/DataCenter.o
	$(CC) $(LIB) -o bin/ProviderTerminal build/ProviderTerminal.o build/DataCenter.o

bin/ManagerTerminal: build/ManagerTerminal.o build/DataCenter.o
	$(CC) $(LIB) -o bin/ManagerTerminal build/ManagerTerminal.o build/DataCenter.o

bin/UnitTests: build/*Test.o
	$(CC) $(LIB) -o bin/UnitTests build/*Test.o

bin/Test: build/DataCenter.o build/ProviderTerminal.o build/ManagerTerminal.o build/Test.o
	$(CC) $(LIB) -o bin/Test build/DataCenter.o  build/ProviderTerminal.o build/ManagerTerminal.o build/Test.o

build/%.o: src/%.cpp
	@mkdir -p build
	$(CC) $(FLAGS) $(INC) -c -o $@ $<
