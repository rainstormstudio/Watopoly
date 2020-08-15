#include "gym.h"


Gym::Gym(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost)
    : Building(square_pos, coord, name, cost) {
        owner = nullptr;
}

unsigned int Gym::getUsageFee() const {
    unsigned int fee = Math::rollTwoDice();
    if (owner) {
        unsigned int gymNum = owner->getGymNum();
        if (gymNum == 1) {
            return (4*fee);
        } else if (gymNum == 2) {
            return (10*fee);
        }
    }
    return 0;
}

void Gym::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
    updatePlayers(players);
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". ");
        if (owner) {
            if (owner != newPlayer && !this->mortgaged) {
                fee = getUsageFee();
                newPlayer->decBalance(fee, owner);
                owner->addBalance(fee);
                if (!newPlayer->getWillBankrupt()) {
                    gfx->addMsg("You paid " + owner->getName() + " $" + std::to_string(fee) + " for gym usage fee. ");
                }
            }
        } else {
            newPlayer->setCanBuy(true);
            gfx->addMsg("This property is not owned. \nIt worths $" + std::to_string(cost) + ". \nDo you want to buy it?. (Yes/No/assets) ");
        }
    }
}

void Gym::render(std::shared_ptr<Graphics> gfx) {
    if (owner) {
        gfx->write(name + "(" + owner->getSymbol() + ")", coordinate.x, coordinate.y, 8);
    } else {
        gfx->write(name, coordinate.x, coordinate.y, 8);
    }
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}



