# Introduction
This project is a continuation of a previous assignment.  The original Genetic Algorithm (GA) has been modified significantly.  These changes include the implementation of selection and crossover as well as a logging function that allows graphs to be made of the run of the GA.  These graphs proved invaluable in understanding and tuning the Baseline GA (BLGA).

![Example Graph of GA Run](doc/img/intro-graph.png)

A couple of population diversity measurements were created to analyze the BLGA.  These measurements were used to create an Enhanced GA (ENGA).  The ENGA uses the diversity measurement to influence the GA. 

The comparison in performance by the BLGA and the ENGA was measured in the number of generations needed to solve a puzzle and the size of the solution.  The ENGA performed better than the BLGA in solution size but performed worse in the number of generations needed.


# Baseline Genetic Algorithm
## Problem Representation
A solution to an 8 puzzle problem can be represented as a series of changes in tile positions.  A single state of the puzzle in this GA is represented by a single 32 bit integer.  The encoding of the state of the puzzle is a simple reading of the numbers in cells 1 to 9 and combining them into a single integer.  For example the following board is encoded as 321456078.

    3 2 1
    4 5 6
    0 7 8

A solution is an ordered list of these board positions.  Internally it is implemented as a doubly linked list and a hash table for fast lookup.

## Initialization of Population
There is an initial growth to the population that is not considered part of the GA.  There is a constant value (30 in this case) that each solution will mutate before the run starts.  The solutions are grown from the initial tile state.  


## Selection Algorithm
The population is sorted according to fitness.  The elite members are then paired with the other members of the population.


## Crossover Algorithm
A single point crossover method is used.  The elite chromosome is iterated from the current state to the first state.  At each position a search is done in the weaker chromosome for a matching position in the elite.  The elite chromosome will then be copied to the weaker at that point.  The left half of the new chromosome will be from the weaker and the right half will be from the elite.  All chromosomes have at least one crossover point, the original board configuration.

## Mutation Algorithm
There are 4 ways a chromosome can mutate.  In each method steps are taken to never create a cycle.  Randomly one of the following are applied on each mutation call:

1. Grow one new move to increase fitness value
2. Grow one new move to a random non-cycling position
3. Modify current board state into random non-cycling position
4. If larger than 31 moves then truncate to a random length else nothing

## Fitness Function
A Manhattan distance and the correctness of the top row and left columns are used in the fitness function.  The Manhattan distance is the sum of the total distance horizontally and vertically to the board goal state.  
The fitness value for a solution is calculated by this formula applied to the current state of the solution:

    Fitness = 1 - Manhattan*0.01 - TopLeft*0.2


## Parameters of GA
These parameters will solve most 8 puzzles in under 150 generations.

* `population size`: 500
* `number of generations`: 500
* `mutation probability`: 1.0
* `crossover probability`: 0.10
* `random seed`: time(0)
* `initial size of solution`: 30
* `elites`: 150 


# Enhanced Genetic Algorithm

To ensure a fair comparison between the ENGA and the BLGA, the parameters of the GA remained the same.  A method for measuring the Manhattan distance between each individual in the population was created and used for visualization.  This method proved too computationally expensive to leave in the final version of the project.  Instead a quicker method for determining diversity was developed.

## Diversity Measurement
Each individual in the population was analyzed and counted to determine the number of unique solutions in the population.  This is done with a simple hash-table counting method.  At the beginning of each generation in the population this calculation is done.

## Controlling Diversity
There are two parameters used to control diversity in the run: maximum number of duplicates and hyper-mutation.  Before the mutation and crossover operations are done on the population, the population's solutions were enumerated and checked against the maximum number of duplicates.

If a solution was present in the population more than the maximum allowed, those chromosomes were hyper-mutated.  This hyper-mutations simply called the mutation operator on the solution N times.  N being the parameter hyper-mutation.

# Experiments
A number of experiments were run for tuning the BLGA before the comparison to the ENGA.  These experiments were simply optimizing the parameters for a balance of solution size and generations needed to complete the run.  When the optimizations were made the parameters were locked between the BLGA and ENGA.

## Tuning the ENGA
In order to compare the ENGA to the BLGA the same random seed was chosen for both during tuning.  The hyper-mutation parameter was modified in 25 percent increments and decrements until the value of 100 was found to be outperforming the BLGA.  The maximum number of duplicates allowed were optimized in the same way.  Maximum number of duplicates was determined to be ten percent of population.

## Comparing BLGA to ENGA
Randomness plays an important role in the function of both GAs so the random seed was seeded with `time(0)` to prevent an artificial bias from being created.  Both GAs were run with two different initial board configurations ten different times.  The number of generations needed and the solution size were averaged over the run of the experiment 

### Sampling of Data

The following graphs have the following parameters graphed:

* `Avg Distance`: This is the average Manhattan distance difference of the entire population to the average Manhattan distance.  This is not used in the GA, it is just an artifact and interesting data point from earlier experimentation.
* `Avg Fitness`: (of population)
* `Best Fitness`: The solution that is ranked highest.
* `Uniques`: This is the percent of unique individuals in the population.

![](doc/img/1.png)
![](doc/img/2.png)
![](doc/img/3.png)
![](doc/img/4.png)
![](doc/img/5.png)
![](doc/img/6.png)

# Results
Both GAs were able to find solutions for each run that was given to them.  The diversity was increased more rapidly in the ENGA as was expected.  The ENGA outperformed the BLGA in the average size of the solution by eight moves.  The ENGA underperformed the BLGA in the average number of generations to find solution by 12.33.

# Analysis
In the BLGA diversity control was never a problem.  This may be because of the design of the GA or the simplicity of the problem.  Perhaps if the GA were designed to find the shortest solution, diversity control may be more necessary.

The ENGA performed fairly well in comparision to the BLGA.  The added computational complexity of the first method of diversity calculation being O(N^2) was too much for quick experimentation.  The uniqueness method that was used for diversity control may be a little too simplistic for robust control of a GA.   

## Description of Source Files

* `world.cpp`: Controls the entire run of the GA.  Seeds the initial population and houses all control parameters.
* `population.cpp`: The data structure for holding the solutions.  Allows the wholesale calling of growth and mutation on solutions.
* `solution.cpp`: The chromosome data structure for each solution.  Methods include mutation and crossover as well as auxiliary methods for getting and checking details of a solution.
* `board.cpp`: The gene data structure for each puzzle state.  The encoding and decoding of each puzzle into an integer and array are located in this file. Logic for movement of tiles and fitness calculations are also located here. 
* `main.cpp`: Parses command line arguments and creates the world.

# Compilation and Running Instructions

These instructions are meant to compile and run the program on a Linux operating system with *make* and *g++* installed. From the command line the following steps are needed:


## Baseline GA
    make build
    ./puzzle <board> 


## Enhanced GA
    make build
    ./puzzle <board> -e



## Notes
The board representation is a 9 character string with the digits 1-8 and an underscore representing zero.  The characters in the string starts in the top-left cell of the 8 puzzle and progresses from left to right until reaching the end of a row and the continues to the next row from left to right.  This is the only required parameter.

*If there are any changes to the source or the compilation is failing a `make clean` might be required before the previous steps.*
