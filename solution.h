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
        int getStatus() const { return list.back(); }
        bool operator<(const Solution& rhs) const;
        double getFitness() const;
};

#endif
