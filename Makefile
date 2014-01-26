CXX=g++
CXXFLAGS=-g -Wall -pedantic -Wno-gnu -Wno-variadic-macros

BOARD=876254301

BIN=puzzle
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

default:
	make build
	./puzzle $(BOARD) 

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm -f $(BIN)

vg: 
	make clean
	make build
	valgrind ./puzzle $(BOARD) 

dbg: 
	make build
	lldb ./puzzle $(BOARD) 

build: $(OBJ)
	$(CXX) -o $(BIN) $^

test: 
	rm -f main.o
	make build
	./puzzle

