CXX=g++
CXXFLAGS=-g -Wall -pedantic
#CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=puzzle

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^
	./puzzle _32871456 50 50 .01 .01

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)

vg: $(OBJ)
	$(CXX) -o $(BIN) $^
	valgrind ./puzzle _32871456 50 50 .01 .01
