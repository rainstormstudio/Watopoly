#include "residence.h"

Residence::Residence(Vec2 coord, std::string name, unsigned int cost)
    : Building(coord, name, cost) {
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

void Residence::update(std::vector<std::shared_ptr<Player>> players) {}

void Residence::render(std::shared_ptr<Graphics> gfx) {
    int len = name.length();
    for (int i = 0; i < len; ++i) {
        gfx->draw(name[i], coordinate.x + i, coordinate.y);
    }
}
