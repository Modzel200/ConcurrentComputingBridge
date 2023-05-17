#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randValue (){
    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand()%5+1;      // Returns a pseudo-random integer between 0 and RAND_MAX
    return r;
}