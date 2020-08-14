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

bool Building::getMortgage() const { return mortgaged; }

void Building::setMortgage(bool SetOrNot) {
    if (mortgaged == true && mortgaged == SetOrNot) {
        std::cout << "Mortgage is already activated!" << std::endl;
        return;
    }
    if (mortgaged == false && mortgaged == SetOrNot) {
        std::cout << "Mortgage is already deactivated!" << std::endl;
        return;       
    }
    mortgaged = SetOrNot;
    if (SetOrNot == true) {
        std::cout << "Mortgage is activated successfully!" << std::endl;
        return;
    } else {
        std::cout << "Mortgage is deactivated successfully!" << std::endl;
        return;       
    }
}

std::string Building::getOwnerName() {
    return owner->getName();
}

void Building::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {}

void Building::render(std::shared_ptr<Graphics> gfx) {}

