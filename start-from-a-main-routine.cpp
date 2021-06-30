#include <stdlib.h>
#include <cstdio>

extern "C" void start_here()
{
    printf("started here\n");
    exit(0);
}

extern "C" void start_there()
{
    printf("started there\n");
    exit(0);
}

// run with:
//  g++ -nostartfiles -Wl,--entry=start_there start-from-a-main-routine.cpp 
