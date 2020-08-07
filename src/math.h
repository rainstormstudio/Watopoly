#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <ctime>

namespace Math {
    // set random seed (call this at initialization of game once)
    void initRandom();

    // get random integer in the interval [min, max]
    int randint(int min, int max);

    // roll a six-sided dice
    unsigned int rollDice();

    // roll two six-sided dice and get the sum
    unsigned int rollTwoDice();
}

#endif
