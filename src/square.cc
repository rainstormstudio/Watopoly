#include "square.h"

Square::Square(Vec2 coord, std::string name)
    : coordinate{coord}, name{name} {
    
}

std::string Square::getName() const { return name; }

void Square::setCoordinate(int x, int y) {
    coordinate.x = x;
    coordinate.y = y;
}
