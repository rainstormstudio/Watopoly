#include "needlesHall.h"

struct NHOption {
    int deltaMoney;
    unsigned int weight;
};

const NHOption options[7] = {
    {-200, 1},
    {-100, 2},
    {-50, 3},
    {25, 6},
    {50, 3},
    {100, 2},
    {200, 1}
};

NeedlesHall::NeedlesHall(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

int NeedlesHall::getOption() {
    unsigned int totalWeight = 0;
    for (int i = 0; i < 7; ++i) {
        totalWeight += options[i].weight;
    }
    int picked = Math::randint(1, totalWeight);
    int result = 0;
    for (int i = 0; i < 7; ++i) {
        picked -= options[i].weight;
        if (picked <= 0) {
            result = options[i].deltaMoney;
            break;
        }
    }
    return result;
}

void NeedlesHall::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
    updatePlayers(players);
    if (newPlayer) {
        gfx->addMsg(newPlayer->getName() + " arrived at Needls Hall");
        deltaMoney = getOption();
        if (deltaMoney >= 0) {
            newPlayer->addBalance(static_cast<unsigned int>(deltaMoney));
            gfx->addMsg(" and gained $" + std::to_string(deltaMoney) + ". \n");
        } else {
            newPlayer->decBalance(static_cast<unsigned int>(-deltaMoney));
            gfx->addMsg(" and lost $" + std::to_string(-deltaMoney) + ". \n");
        }
        int pick = Math::randint(1, 100);
        if (pick == 1) {
            unsigned int totalTimsCups = 0;
            for (auto& player : players) {
                totalTimsCups += player->getTimsCups();
            }
            if (totalTimsCups < 4) {
                newPlayer->setTimsCups(newPlayer->getTimsCups() + 1);
                gfx->addMsg("Congratulations! You won a Roll Up the Rim cup.\n");
            }
        }
    }
}

void NeedlesHall::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}

