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

std::string Residence::getType() {
    return "Residence";
}

void Residence::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    if (!owner) {
        if (newPlayer) {
            newPlayer->setCanBuy(true);
        }
    }
}

void Residence::render(std::shared_ptr<Graphics> gfx) {
    int len = name.length();
    for (int i = 0; i < len; ++i) {
        gfx->draw(name[i], coordinate.x + i, coordinate.y);
    }
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ".");
        if (newPlayer->getCanBuy()) {
            gfx->addMsg("This property is not owned. Do you want to buy it?. (Yes/No) It worths " + std::to_string(cost) + ".");
        }
    }
}
