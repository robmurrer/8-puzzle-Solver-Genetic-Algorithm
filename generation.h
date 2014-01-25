#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <algorithm>
#include "solution.h"

using namespace std;

class Generation
{

    public:
        int id;
        vector<Solution> solutions;
        Generation(int, int, int);
        void prepareSort();
        bool checkSolved();
        void printVerbose();
        void grow();
        void growBest();
        bool cycle();

};

#endif
