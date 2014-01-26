#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "solution.h"
#include "dbh.h"

bool test_checkCycle()
{
    srand(0);
    Solution sol(123456780);
    sol.grow();
    sol.grow();
    sol.grow();
    check_debug(sol.checkCycle(), "Did not detect cycle");
    return true;
error:
    return false;

}

bool test_grow_best()
{

    check_debug(Board(123456780).getFitness() == 1.0, "Wrong Fitness, should be 1.0");
    return true;

error:
    return false;
}

bool test_test()
{
    printf("Testing Tests\n");
    return true;
}


bool (*tests[])() = 
{ 
    test_checkCycle,
    test_grow_best,
    test_test 
};
      

void run_tests()
{
    int i = 0;
    while(tests[i] != NULL)
        (*tests[i++])();
        
}

