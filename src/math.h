#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <ctime>

namespace Math {
    // set random seed (call this at initialization of game once)
    void initRandom() {
        srand(time(NULL));
    }

    // get random integer in the interval [min, max]
    int randint(int min, int max) {
        return min + rand() * (max + 1 - min);
    }

    // roll a six-sided dice
    unsigned int rollDice() {
        return randint(1, 6);
    }

    // roll two six-sided dice and get the sum
    unsigned int rollTwoDice() {
        return rollDice() + rollDice();
    }
}

#endif
