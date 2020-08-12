#include "collectOSAP.h"

CollectOSAP::CollectOSAP(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {
}

void CollectOSAP::addPlayer(std::shared_ptr<Player> initPlayer) {
    players.clear();
    players.push_back(initPlayer);
}

void CollectOSAP::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    unsigned int OSAPFee = 200;
    if (newPlayer) {
        newPlayer->addBalance(OSAPFee);
    }
}

void CollectOSAP::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " received $200 for OSAP fee. ");
    }
}
