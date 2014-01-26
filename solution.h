#include <map>
#include <deque>
#include "board.h"

#ifndef SOLUTION_H 
#define SOLUTION_H 

using namespace std;

class Solution
{
    public:
        multimap<int, int> map; 
        deque<int> list;
        
    public:
        Solution(int);
        void grow(); 
        bool growNoCycle(); 
        void growBest(); 
        void growBestNoCycle(); 
        void mutate();
        int getStatus() const;
        bool operator<(const Solution& rhs) const;
        double getFitness() const;
        bool solved();
        void print();
        bool checkCycle();
};

#endif
