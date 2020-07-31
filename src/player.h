#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

class Graphics;
class Building;

class Player {
    std::string name;
    char symbol;
    unsigned int position;
    int balance;

public:
    Player(std::string name, char symbol);

    std::string getName() const;
    char getSymbol() const;

    unsigned int getPosition() const;
    void setPosition(unsigned int pos);

    void render(Graphics & gfx);
};

#endif
