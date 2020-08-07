#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <ctime>
#include <string>

namespace Math {
    // set random seed (call this at initialization of game once)
    void initRandom();

    // get random integer in the interval [min, max]
    int randint(int min, int max);

    // roll a six-sided dice
    unsigned int rollDice();

    // roll two six-sided dice and get the sum
    unsigned int rollTwoDice();

    // checks if a string is a natural number
    bool isNat(std::string str);
}

#endif
