#include "building.h"

Building::Building(Vec2 coord, std::string name, unsigned int cost) 
    : Square(coord, name), cost{cost} {
        owner = nullptr;
}

std::shared_ptr<Player> Building::getOwner() const { return owner; }

void Building::setOwner(std::shared_ptr<Player> player) {
    owner = player;
}

unsigned int Building::getCost() const { return cost; }

void Building::update(std::vector<std::shared_ptr<Player>> players) {}

void Building::render(std::shared_ptr<Graphics> gfx) {}

