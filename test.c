#include <stdio.h>

bool test_test()
{
    printf("Testing Tests\n");
    return true;
}


bool (*tests[])() = { test_test };
      

void run_tests()
{
    int i = 0;
    while(tests[i] != NULL)
        (*tests[i++])();
        
}

