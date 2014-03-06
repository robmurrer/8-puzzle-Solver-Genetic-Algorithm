#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <algorithm>
#include "solution.h"

using namespace std;

class Population
{
    private:
        int id;
        vector<Solution> solutions;

    public:
        Population(int, int, int);
        void sort();
        void age();
        bool checkSolved();
        Solution getBest();
        void printVerbose();
        void printSummary();
        void grow();
        void growBest(int);
        void mutate(int);
        bool cycle();
        void checkCycles();
        void selection(int, int);

};

#endif
