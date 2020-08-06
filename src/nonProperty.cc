#include "nonProperty.h"

NonProperty::NonProperty(Vec2 coord, std::string name)
    : Square(coord, name) {

}

void NonProperty::update(std::shared_ptr<Player> player) {}

void NonProperty::render(std::shared_ptr<Graphics> gfx) {}
