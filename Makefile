CXX=g++
CXXFLAGS=-g -Wall -pedantic -Wno-gnu -Wno-variadic-macros


#to easy
#BOARD=_13425786

#solves
#BOARD=_32871456

#hardest
BOARD=8672543_1

BIN=puzzle
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

test: 
	rm -f main.o
	make build
	valgrind ./puzzle > test.txt 2>&1

run:
	make build
	valgrind ./puzzle $(BOARD) 

fast:
	make build
	./puzzle $(BOARD) 

build: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm -f $(BIN)

dbg: 
	make build
	lldb ./puzzle 


