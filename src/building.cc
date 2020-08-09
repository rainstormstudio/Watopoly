#include "building.h"

Building::Building(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost) 
    : Square(square_pos, coord, name), cost{cost} {
        owner = nullptr;
        mortgaged = false;
}

std::shared_ptr<Player> Building::getOwner() const { return owner; }

void Building::setOwner(std::shared_ptr<Player> player) {
    owner = player;
}

unsigned int Building::getCost() const { return cost; }

void Building::setMortgage() {
    if (mortgaged == true) {
        std::cout << "Mortgage is already activated!" << std::endl;
        return;
    }
    mortgaged = true;
    std::cout << "Mortgage is activated successfully!" << std::endl;
    return;
}

void Building::removeMortgage() {
    if (mortgaged == false) {
        std::cout << "Mortgage is already deactivated" << std::endl;
        return;
    }
    mortgaged = false;
    std::cout << "Mortgage is deactivated successfully!" << std::endl;
    return;
}

std::string Building::getOwnerName() {
    return owner->getName();
}

std::string Building::getType() {
    return "Property";
}

void Building::update(std::vector<std::shared_ptr<Player>> players) {}

void Building::render(std::shared_ptr<Graphics> gfx) {}

