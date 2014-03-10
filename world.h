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
        bool enhanced;
        Population population;
        void seedPopulation();

        
    public:
        World(int, bool);
        void start();
        bool solved;
};

#endif
