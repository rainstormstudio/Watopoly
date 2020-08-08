#include "DCtims.h"

DCtims::DCtims(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

void DCtims::update(std::vector<std::shared_ptr<Player>> players) {
    // need to consider different cases
    this->players.clear();
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i]->getPosition() == square_pos) {
            this->players.push_back(players[i]);
        }
    }
}

void DCtims::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}

