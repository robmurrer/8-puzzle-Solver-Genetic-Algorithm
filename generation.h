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
        int unchecked_growth;

        vector<Solution> solutions;
        

    public:
        Generation(int, int, int);
        Generation(Generation&, int, double, double);
        void age();
        void print();
        bool cycle();
        Solution getFittest() { return solutions[0]; }
        Solution getFittest(int i) { return solutions[i]; }
        int getSize() { return size; }
        int getId() { return id; }

};

#endif
