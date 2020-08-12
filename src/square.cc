#include "square.h"

Square::Square(unsigned int square_pos, Vec2 coord, std::string name)
	: square_pos{ square_pos }, coordinate { coord }, name{ name } {
    
}

void Square::updatePlayers(std::vector<std::shared_ptr<Player>> mplayers) {
    newPlayer = nullptr;
    for (unsigned int i = 0; i < mplayers.size(); ++i) {
        if (mplayers[i]->getPosition() == square_pos) {
            newPlayer = mplayers[i];
            for (auto &currentPlayer : this->players) {
                if (mplayers[i] == currentPlayer) {
                    newPlayer = nullptr;
                    break;
                }
            }
        }
    }
    this->players.clear();
    for (unsigned int i = 0; i < mplayers.size(); ++i) {
        if (mplayers[i]->getPosition() == square_pos) {
            this->players.push_back(mplayers[i]);
        }
    }
}

std::string Square::getName() const { return name; }

void Square::setCoordinate(int x, int y) {
    coordinate.x = x;
    coordinate.y = y;
}