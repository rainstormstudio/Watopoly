#include "nonProperty.h"

NonProperty::NonProperty(unsigned int square_pos, Vec2 coord, std::string name)
    : Square(square_pos, coord, name) {

}

//void NonProperty::setMortgage() {}

//void NonProperty::removeMortgage() {}

std::string NonProperty::getOwnerName() {
    return "NonProperty";
}

void NonProperty::update(std::vector<std::shared_ptr<Player>> players) {}

void NonProperty::render(std::shared_ptr<Graphics> gfx) {}
