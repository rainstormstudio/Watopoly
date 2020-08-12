#include "academicBuilding.h"

Academics::Academics(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost,
                     std::string block, unsigned int improvementCost, 
                     unsigned int tuition_0, unsigned int tuition_1, 
                     unsigned int tuition_2, unsigned int tuition_3,
                     unsigned int tuition_4, unsigned int tuition_5)
    : Building(square_pos, coord, name, cost), block{block}, improvementCost{improvementCost} {
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

void Academics::setImprovement(unsigned int value) {
    if (0 <= value && value <= 5) {
        improvement = value;
    }
}

unsigned int Academics::getImprovement() const { return improvement; }

bool Academics::addImprovement() {
    if (improvement == 5) return false;
    ++improvement;
    return true;
}

bool Academics::removeImprovement() {
    if (improvement == 0) return false;
    --improvement;
    return true;
}

void Academics::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    if (!owner) {
        if (newPlayer) {
            newPlayer->setCanBuy(true);
        }
    }
}

void Academics::render(std::shared_ptr<Graphics> gfx) {
    for (unsigned int i = 0; i < improvement; ++i) {
        gfx->draw('*', coordinate.x + i, coordinate.y);
    }
    gfx->write("--------", coordinate.x, coordinate.y + 1, 8);
    if (owner) {
        gfx->write(name + "(" + owner->getSymbol() + ")", coordinate.x, coordinate.y + 2, 8);
    } else {
        gfx->write(name, coordinate.x, coordinate.y + 2, 8);
    }
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at " + name + ". ");
        if (newPlayer->getCanBuy()) {
            gfx->addMsg("This property is not owned. It worths " + std::to_string(cost) + ". Do you want to buy it?. (Yes/No) ");
        }
    }
}
