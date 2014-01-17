#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <algorithm>
#include "solution.h"

using namespace std;

class Generation
{
    private:
        int size;
        int id;
        vector<Solution> solutions;
        

    public:
        Generation(int id, int size, int boardStart);
        void age();
        void print();
        bool cycle();

};

#endif
