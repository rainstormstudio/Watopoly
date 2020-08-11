#ifndef SQUARE_H
#define SQUARE_H

#include "types.h"
#include "graphics.h"
#include "player.h"

class Square {
protected:
	unsigned int square_pos;
    Vec2 coordinate;    // defines the coordinate of the square on the gameboard
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Player> newPlayer;
    std::string name;
public:
    Square(unsigned int square_pos, Vec2 coord, std::string name);

    std::string getName() const;

    void setCoordinate(int x, int y);
    
    void updatePlayers(std::vector<std::shared_ptr<Player>> players);

    //virtual void setMortgage() = 0;

    //virtual void removeMortgage() = 0;

    virtual std::string getOwnerName() = 0;

    virtual void update(std::vector<std::shared_ptr<Player>> players) = 0;

    virtual void render(std::shared_ptr<Graphics> gfx) = 0;
};

#endif
