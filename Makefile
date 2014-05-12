CXX=g++
CXXFLAGS=-g -Wall -pedantic -Wno-gnu -Wno-variadic-macros


#to easy
#BOARD=_13425786

#solves
#BOARD=_32871456

#hardest
BOARD=8672543_1

#BOARD=8762543_1

BIN=puzzle
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)


compare:
	make plot
	make plot_enhanced

plot:
	make fast
	make genplot

plot_enhanced:
	make fast_enhanced
	make genplot

genplot:
	gnuplot -e "set term png; set out \"log/`cat log/file.txt`.png\"; set xlabel \"Generation\"; \
	    set title \"`cat log/title.txt`\"; set grid; \
	    plot \"log/data.txt\" using 2 title 'Avg Distance' with lines, \
	    \"log/data.txt\" using 3 title 'Avg Fitness' with lines, \
	    \"log/data.txt\" using 4 title 'Best Fitness' with lines, \
	    \"log/data.txt\" using 5 title 'Uniques' with lines"
	open log/`cat log/file.txt`.png
	#make crossover

crossover:
	gnuplot -e "set term png; set out \"log/`cat log/file.txt`-xover.png\"; set xlabel \"Crossover Counter\"; set ylabel \"Crossover point\"; set grid;\
	    set title \"`cat log/title.txt`\"; set grid; \
	    plot \"log/crossover.txt\" using 2 title 'Chromosome A', \
	    \"log/crossover.txt\" using 3 title 'Chromosome B'"
	open log/`cat log/file.txt`-xover.png
test: 
	rm -f main.o
	make build
	valgrind ./puzzle > test.txt 2>&1

run:
	make build
	valgrind ./puzzle $(BOARD) 

run_enhanced:
	make build
	valgrind ./puzzle $(BOARD) -e

fast:
	make build
	./puzzle $(BOARD) 

fast_enhanced:
	make build
	./puzzle $(BOARD) -e

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

