FLAGS=-g -Wall -std=c++14
LIB=-pthread
CC=g++
INC=-I include

SOURCES=$(shell find src -type f -name *.cpp)

all: DIRECTORIES bin/Demo
terminals: DIRECTORIES bin/ManagerTerminal bin/ProviderTerminal 

DIRECTORIES:
	mkdir -p build bin manager_reports member_reports provider_reports

clean:
	rm -rf build bin manager_reports member_reports provider_reports

bin/ProviderTerminal: build/ProviderTerminal.o build/DataCenter.o build/Reporter.o
	$(CC) $(LIB) -o bin/ProviderTerminal build/ProviderTerminal.o build/DataCenter.o build/Reporter.o

bin/ManagerTerminal: build/ManagerTerminal.o build/DataCenter.o build/Reporter.o
	$(CC) $(LIB) -o bin/ManagerTerminal build/ManagerTerminal.o build/DataCenter.o build/Reporter.o

bin/UnitTests: build/*Test.o
	$(CC) $(LIB) -o bin/UnitTests build/*Test.o

bin/Demo: build/DataCenter.o build/ProviderTerminal.o build/ManagerTerminal.o build/Demo.o build/Reporter.o
	$(CC) $(LIB) -o bin/Demo build/DataCenter.o  build/ProviderTerminal.o build/ManagerTerminal.o build/Demo.o build/Reporter.o

build/%.o: src/%.cpp
	$(CC) $(FLAGS) $(INC) -c -o $@ $<
