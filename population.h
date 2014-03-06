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
        double avgDistance;
        double meanDistance;

    public:
        Population(int, int, int);
        void prepareSort();
        void age();
        bool checkSolved();
        Solution getBest();
        void printVerbose();
        void printSummary();
        void grow();
        void growBest(int);
        bool cycle();
        void checkCycles();
        void selection(int, int);
        void calcDiversity();

};

#endif
