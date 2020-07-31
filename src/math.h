#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <ctime>

namespace Math {

    void initRandom() {
        srand(time(NULL));
    }

    int randint(int min, int max) {
        return min + rand() * (max + 1 - min);
    }
}

#endif
