#include "tuition.h"

Tuition::Tuition(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

void Tuition::update(std::vector<std::shared_ptr<Player>> players) {
    this->players.clear();
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getPosition() == square_pos) {
            // choose betweeen two options
            this->players.push_back(players[i]);
        }
    }
}

void Tuition::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    // print something?
}


