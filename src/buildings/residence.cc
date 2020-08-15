#include "residence.h"

Residence::Residence(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost)
    : Building(square_pos, coord, name, cost) {
        owner = nullptr;
}

unsigned int Residence::getRent() const {
    if (owner == nullptr) {
        return 0;
    } else {
        unsigned int ResiNum = owner->getResiNum();
        if (ResiNum <= 4 && ResiNum >= 0) {
            return (25*ResiNum);
        } else {
            // for debugging use;
            std::cerr << "Invalid ResiNum" << std::endl;
            return 0;
        }
    }
}

void Residence::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
    updatePlayers(players);
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". ");
        if (owner) {
            if (owner != newPlayer) {
                fee = getRent();
                newPlayer->decBalance(fee);
                owner->addBalance(fee);
                gfx->addMsg("You paid " + owner->getName() + " $" + std::to_string(fee) + " for residence rent. ");
            }
        } else {
            newPlayer->setCanBuy(true);
            gfx->addMsg("This property is not owned. \nIt worths $" + std::to_string(cost) + ". \nDo you want to buy it?. (Yes/No/assets) ");
        }
    }
}

void Residence::render(std::shared_ptr<Graphics> gfx) {
    if (owner) {
        gfx->write(name + "(" + owner->getSymbol() + ")", coordinate.x, coordinate.y, 8);
    } else {
        gfx->write(name, coordinate.x, coordinate.y, 8);
    }
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}
