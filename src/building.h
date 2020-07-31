#ifndef BUILDING_H
#define BUILDING_H

#include "square.h"
#include "types.h"

class Building : public Square {
protected:
    unsigned int cost;
    std::shared_ptr<Player> owner;
public:
    Building(unsigned int pos, std::string name, unsigned int cost);

    std::shared_ptr<Player> getOwner() const;
    void setOwner(std::shared_ptr<Player> player);

    unsigned int getCost() const;

    void notify(std::shared_ptr<Player> player) override;
};

#endif
