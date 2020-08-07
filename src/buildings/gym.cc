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
    this->players.clear();
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getPosition() == square_pos) {
            this->players.push_back(players[i]);
        }
    }
}

void Gym::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}



