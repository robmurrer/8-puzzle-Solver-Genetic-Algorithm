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
        int origin;
        vector<Solution> solutions;
        

    public:
        Generation(int id, int size, int boardStart);
        Generation(Generation&, int);
        void age();
        void print();
        bool cycle();
        Solution getFittest() { return solutions[0]; }
        Solution getFittest(int i) { return solutions[i]; }
        int getSize() { return size; }
        int getId() { return id; }

};

#endif
