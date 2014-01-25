CXX=g++
CXXFLAGS=-g -Wall -pedantic -Wno-gnu -Wno-variadic-macros

#CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=puzzle

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

default:
	rm -f main.o
	make all

all: $(OBJ)
	$(CXX) -o $(BIN) $^
	./puzzle _32871456 
	#./puzzle 158_23467 

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)

vg: $(OBJ)
	$(CXX) -o $(BIN) $^
	valgrind ./puzzle _32871456 

dbg: $(OBJ)
	$(CXX) -o $(BIN) $^
	lldb ./puzzle 158_23467 

build: $(OBJ)
	$(CXX) -o $(BIN) $^
