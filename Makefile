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

plot:
	make fast
	gnuplot -e "set term png; set out \"log/`cat log/file.txt`.png\"; set xlabel \"Generation\"; \
	    set title \"`cat log/title.txt`\"; set grid; \
	    plot \"log/data.txt\" using 2 title 'Avg Distance' with lines, \
	    \"log/data.txt\" using 3 title 'Avg Fitness' with lines, \
	    \"log/data.txt\" using 4 title 'Best Fitness' with lines"
	open log/`cat log/file.txt`.png

