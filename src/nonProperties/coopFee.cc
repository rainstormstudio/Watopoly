#include "coopFee.h"

CoopFee::CoopFee(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

void CoopFee::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
    updatePlayers(players);
    if (newPlayer) {
        newPlayer->decBalance(150, nullptr);
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". \n");
        gfx->addMsg("You paid $150 for coop fee. ");
    }
}

void CoopFee::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 5);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}
