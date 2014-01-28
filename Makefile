CXX=g++
CXXFLAGS=-g -Wall -pedantic -Wno-gnu -Wno-variadic-macros

# can't solve this one
#BOARD=12345687_

# can't solve this one
#BOARD=8762543_1

#solves
BOARD=_32871456

BIN=puzzle
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

default:
	make build
	./puzzle $(BOARD) 

build: $(OBJ)
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
	lldb ./puzzle 

test: 
	rm -f main.o
	make build
	./puzzle

