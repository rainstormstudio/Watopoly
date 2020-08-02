#ifndef SQUARE_H
#define SQUARE_H

#include "types.h"
#include "graphics.h"

class Player;

class Square {
protected:
    unsigned int position;
    Vec2 coordinate;    // defines the coordinate of the square on the gameboard
    std::string name;
public:
    Square(unsigned int pos, std::string name);

    unsigned int getPosition() const;
    std::string getName() const;

    void setCoordinate(int x, int y);

    virtual void notify(std::shared_ptr<Player> player) = 0;

    virtual void render(Graphics & gfx) = 0;
}

#endif
