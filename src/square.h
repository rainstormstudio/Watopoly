#ifndef SQUARE_H
#define SQUARE_H

#include "types.h"

class Player;

class Square {
protected:
    unsigned int position;
    std::string name;
public:
    Square(unsigned int pos, std::string name);

    unsigned int getPosition() const;
    std::string getName() const;

    virtual void notify(std::shared_ptr<Player> player) = 0;
}

#endif
