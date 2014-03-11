#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include <algorithm>
#include "solution.h"

using namespace std;

class Population
{
    private:
        int id;
        vector<Solution> solutions;
        map<int,int> uniques;
        double avgDistance;
        double meanDistance;
        double avgFitness;

    public:
        Population(int, int, int);
        void sort();
        void age();
        bool checkSolved();
        Solution getBest();
        void printVerbose();
        void printSummary();
        void grow();
        void growBest(int);
        void mutate(int);
        bool cycle();
        void checkCycles();
        void selection(int, int);
        void calcDiversity();
        double getMeanDistance() { return meanDistance; }
        double getAvgFitness();
        int getUniqueIndividuals();
        void controlDiversity(int,int);

};

#endif
