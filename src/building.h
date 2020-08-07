#ifndef BUILDING_H
#define BUILDING_H

#include "square.h"
#include "types.h"
#include "player.h"
#include "math.h"

class Building : public Square {
protected:
    unsigned int cost;
    std::shared_ptr<Player> owner;
public:
    Building(Vec2 coord, std::string name, unsigned int cost);

    std::shared_ptr<Player> getOwner() const;
    void setOwner(std::shared_ptr<Player> player);

    unsigned int getCost() const;

    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;

};

#endif
