#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "population.h"
#include <map>

Population::Population(int _id, int size, int _boardStart)
{
    id = _id;
    solutions.reserve(size);

    vector<Solution>::iterator it = solutions.begin(); 

    for (int i=0; i<size; i++)
        it = solutions.insert(it, Solution(_boardStart));
}

void Population::grow()
{
    for (int i=0; i<solutions.size(); i++)
        //solutions[i].grow();
        solutions[i].growNoCycle();
}

void Population::growBest(int pm)
{
    for (int i=0; i<solutions.size(); i++)
    {
        // only mutate with a certain probability
        int r = rand() % pm;
        if (r==0)
            solutions[i].growBestNoCycle();
    }
}

Solution Population::getBest()
{
    return solutions[0];
}
    
bool Population::checkSolved()
{
    return solutions[0].solved();
}

void Population::sort()
{
    std::sort(solutions.begin(), solutions.end());
}
void Population::printVerbose()
{
    printf("Generation: %d adist: %f mdist: %f\n", id, avgDistance, meanDistance);
    for (int i=0; i<solutions.size(); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f adist: %f mdist %f\n", solutions[i].getFitness(), solutions[i].getAvgDistance(), solutions[i].getMeanDistance()); 
    }
}

void Population::printSummary()
{
    printf("Generation: %d adist: %f mdist: %f\n", id, avgDistance, meanDistance);
    for (int i=0; i<(int)(.05*solutions.size()); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f adist: %f mdist %f\n", solutions[i].getFitness(), solutions[i].getAvgDistance(), solutions[i].getMeanDistance()); 
    }
}


void Population::selection(int elites, int cm)
{
   for (int i=elites; i<solutions.size(); i++)
   {
        // only crossover with certain probability
        int r = rand() % cm;
        if (r==0)
            solutions[i].crossover(solutions[i%elites]);
   }
}

void Population::checkCycles()
{
    for (int i=0; i<solutions.size(); i++)
        if (solutions[i].checkCycle())
            printf("Cycle Found\n");
}

void Population::age()
{ 
    id++;
}


void Population::calcDiversity()
{
    // for the population used as simple counter until end 
    avgDistance = 0;
    
    for (int i=0; i<solutions.size(); i++)
    {
        int distance = 0;
        Board iboard(solutions[i].getStatus());

        for(int j=0; j<solutions.size(); j++)
        {
            // don't do calc on self
            if (i==j) continue;
            distance += iboard.getDistance(solutions[j].getStatus());
        }
        
        // for individual
        double pAvgDistance = (double)distance/(solutions.size() - 1);

        // for population
        avgDistance += pAvgDistance;
        solutions[i].setAvgDistance(pAvgDistance);
    }

    // create actual average
    avgDistance = avgDistance / solutions.size();

    meanDistance = 0;
    for (int i=0; i<solutions.size(); i++)
    {
        double pMeanDistance = fabs(solutions[i].getAvgDistance() - avgDistance);
        meanDistance += pMeanDistance;
        solutions[i].setMeanDistance(pMeanDistance);
    }

    meanDistance = meanDistance / solutions.size();

}


void Population::mutate(int mrate)
{
    for (int i=0; i<solutions.size(); i++)
    {
        int r = rand() % mrate;
        if (r == 0)
        {
            r = rand() % 4;
            if (r == 0) solutions[i].growBestNoCycle();
            if (r == 1) solutions[i].growNoCycle();
            if (r == 2) solutions[i].mutate();
            if (r == 3) solutions[i].truncate();
        }
    }
}

double Population::getAvgFitness()
{
    avgFitness = 0;

    for(int i=0; i<solutions.size(); i++)
        avgFitness += solutions[i].getFitness();

    avgFitness /= solutions.size();
    return avgFitness;
}

int Population::getUniqueIndividuals()
{
    // clear hash
    uniques.clear();
    for (int i=0; i<solutions.size(); i++)
    {
        // not in hash yet
        if (uniques.count(solutions[i].getStatus()) == 0)
        {
            uniques.insert(make_pair(solutions[i].getStatus(), 1));
        }

        // already in hash so update count
        else
        {
            uniques[solutions[i].getStatus()]++;
        }

    }
    return uniques.size();
}

void Population::controlDiversity(int max_uniques, int hyper)
{
    for (int i=0; i<solutions.size(); i++)
    {
        if (uniques[solutions[i].getStatus()] > max_uniques)
        {
            uniques[solutions[i].getStatus()]--;

            // hyper mutate
            for (int j=0; j<hyper; j++) solutions[i].mutate();
        }
    }
}
            

            
