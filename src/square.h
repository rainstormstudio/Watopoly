#ifndef SQUARE_H
#define SQUARE_H

#include "types.h"
#include "graphics.h"

class Player;

class Square {
protected:
    Vec2 coordinate;    // defines the coordinate of the square on the gameboard
    std::vector<std::shared_ptr<Player>> players;
    std::string name;
public:
    Square(Vec2 coord, std::string name);

    std::string getName() const;

    void setCoordinate(int x, int y);

    virtual void update(std::shared_ptr<Player> player) = 0;

    virtual void render(std::shared_ptr<Graphics> gfx) = 0;
};

#endif
