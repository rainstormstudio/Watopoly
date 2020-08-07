#include "gym.h"


Gym::Gym(Vec2 coord, std::string name, unsigned int cost)
    : Building(coord, name, cost) {
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

void Gym::update(std::vector<std::shared_ptr<Player>> players) {}

void Gym::render(std::shared_ptr<Graphics> gfx) {
    int len = name.length();
    for (int i = 0; i < len; ++i) {
        gfx->draw(name[i], coordinate.x + i, coordinate.y);
    }
}



