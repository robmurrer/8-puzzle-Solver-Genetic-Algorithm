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
        void age() { id++;};
        bool checkSolved();
        Solution getBest();
        void printVerbose();
        void grow();
        void growBest();
        bool cycle();

};

#endif
