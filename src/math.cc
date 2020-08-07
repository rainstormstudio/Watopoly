#include "math.h"

// set random seed (call this at initialization of game once)
void Math::initRandom() {
    srand(time(NULL));
}

// get random integer in the interval [min, max]
int Math::randint(int min, int max) {
    return min + rand() * (max + 1 - min);
}

// roll a six-sided dice
unsigned int Math::rollDice() {
    return randint(1, 6);
}

// roll two six-sided dice and get the sum
unsigned int Math::rollTwoDice() {
    return rollDice() + rollDice();
}

bool Math::isNat(std::string str) {
    int len = str.length();
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
    }
    return true;
}