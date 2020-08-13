#include "tuition.h"

Tuition::Tuition(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

void Tuition::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    if (newPlayer) {
        newPlayer->setNeedToPayTuition(true);
    }
}

void Tuition::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". ");
        gfx->addMsg("Choose to pay $300 or 10% of your total worth! ");
        gfx->addMsg("Type 1 for the first option, 2 for the second one.");
    }
}


