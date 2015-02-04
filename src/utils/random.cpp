#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils/random.h"

void seedRandomGenerator()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }
}

int getRandomInt(int maxValue)
{
    seedRandomGenerator();
    return rand() % maxValue;
}

float getRandomFloat()
{
    seedRandomGenerator();
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}


