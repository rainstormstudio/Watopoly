#include "building.h"

Building::Building(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost) 
    : Square(square_pos, coord, name), cost{cost} {
        owner = nullptr;
}

std::shared_ptr<Player> Building::getOwner() const { return owner; }

void Building::setOwner(std::shared_ptr<Player> player) {
    owner = player;
}

unsigned int Building::getCost() const { return cost; }

void Building::update(std::vector<std::shared_ptr<Player>> players) {}

void Building::render(std::shared_ptr<Graphics> gfx) {}

