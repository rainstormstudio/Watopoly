#include "academicBuilding.h"

Academics::Academics(Vec2 coord, std::string name, unsigned int cost,
                     std::string block, unsigned int improvementCost, 
                     unsigned int tuition_0, unsigned int tuition_1, 
                     unsigned int tuition_2, unsigned int tuition_3,
                     unsigned int tuition_4, unsigned int tuition_5)
    : Building(coord, name, cost), block{block}, improvementCost{improvementCost} {
    tuitions[0] = tuition_0;
    tuitions[1] = tuition_1;
    tuitions[2] = tuition_2;
    tuitions[3] = tuition_3;
    tuitions[4] = tuition_4;
    tuitions[5] = tuition_5;
}

std::string Academics::getBlock() const { return block; }

unsigned int Academics::getTuition(unsigned int index) const { return tuitions[index]; }

unsigned int Academics::getImprovementCost() const { return improvementCost; }

unsigned int Academics::getImprovement() const { return improvement; }

void Academics::update(std::vector<std::shared_ptr<Player>> players) {

}

void Academics::render(std::shared_ptr<Graphics> gfx) {
    for (int i = 0; i < 8; ++i) {
        gfx->draw('-', coordinate.x + i, coordinate.y + 1);
    }
    int len = name.length();
    for (int i = 0; i < len; ++i) {
        gfx->draw(name[i], coordinate.x + i, coordinate.y + 2);
    }
}
