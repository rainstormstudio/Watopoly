#include "square.h"

Square::Square(unsigned int square_pos, Vec2 coord, std::string name)
	: square_pos{ square_pos }, coordinate { coord }, name{ name } {
    
}

std::string Square::getName() const { return name; }

void Square::setCoordinate(int x, int y) {
    coordinate.x = x;
    coordinate.y = y;
}