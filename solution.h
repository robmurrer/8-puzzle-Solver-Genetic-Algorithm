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
        int getStatus() { return list.back(); }
};

#endif
