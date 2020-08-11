#include "gym.h"


Gym::Gym(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost)
    : Building(square_pos, coord, name, cost) {
        owner = nullptr;
}

unsigned int Gym::getUsageFee() const {
    unsigned int fee = Math::rollTwoDice();
    if (owner == nullptr) {
        return 0;
    } else {
        unsigned int GymNum = owner->getGymNum();
        if (GymNum == 1) {
            return (4*fee);
        } else {
            return (10*fee);
        }
    }
}

void Gym::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    if (!owner) {
        if (newPlayer) {
            newPlayer->setCanBuy(true);
        }
    }
}

void Gym::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". ");
        if (newPlayer->getCanBuy()) {
            gfx->addMsg("This property is not owned. Do you want to buy it?. (Yes/No) It worths " + std::to_string(cost) + ". ");
        }
    }
}



