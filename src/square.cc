#include "square.h"

Square::Square(unsigned int square_pos, Vec2 coord, std::string name)
	: square_pos{ square_pos }, coordinate { coord }, name{ name } {
    
}

void Square::updatePlayers(std::vector<std::shared_ptr<Player>> players) {
    this->players.clear();
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getPosition() == square_pos) {
            this->players.push_back(players[i]);
        }
    }
}


std::string Square::getName() const { return name; }

void Square::setCoordinate(int x, int y) {
    coordinate.x = x;
    coordinate.y = y;
}