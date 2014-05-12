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
