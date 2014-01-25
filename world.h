#ifndef _WORLD_H_
#define _WORLD_H_
#include "generation.h"
using namespace std;


class World
{
    private:
        int pop_size;
        int num_gens;
        double mutation;
        double crossover;
        int origin;

        Generation population;

        
    public:
        World(int, int, int, double, double);
        void start();
        bool solved;
};

#endif