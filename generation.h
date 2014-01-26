#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <algorithm>
#include "solution.h"

using namespace std;

class Generation
{
    private:
        int id;
        vector<Solution> solutions;

    public:
        Generation(int, int, int);
        void prepareSort();
        void age();
        bool checkSolved();
        Solution getBest();
        void printVerbose();
        void printSummary();
        void grow();
        void growBest();
        bool cycle();
        void checkCycles();
        void selection(int);

};

#endif
