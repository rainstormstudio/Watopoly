#include "nonProperty.h"

NonProperty::NonProperty(Vec2 coord, std::string name)
    : Square(coord, name) {

}

void NonProperty::update(std::vector<std::shared_ptr<Player>> players) {}

void NonProperty::render(std::shared_ptr<Graphics> gfx) {}
