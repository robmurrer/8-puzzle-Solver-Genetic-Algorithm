#ifndef _WORLD_H_
#define _WORLD_H_
#include "population.h"
using namespace std;


class World
{
    private:
        int pop_size;
        int num_gens;
        int mutation;
        int crossover;
        int origin;
        int elites;
        Population population;
        void seedPopulation();

        
    public:
        World(int);
        World(int, int, int, double, double);
        void start();
        bool solved;
};

#endif
