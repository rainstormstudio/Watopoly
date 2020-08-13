#include "slc.h"

struct SLCOption {
    SLCmove move;
    unsigned int weight;
};

const SLCOption options[8] = {
    {BACK_3, 3},
    {BACK_2, 4},
    {BACK_1, 4},
    {FORWARD_1, 3},
    {FORWARD_2, 4},
    {FORWARD_3, 4},
    {GO_TO_DCtims, 1},
    {GO_TO_COSAP, 1}
};

SLC::SLC(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

SLCmove SLC::getOption() {
    unsigned int totalWeight = 0;
    for (int i = 0; i < 8; ++i) {
        totalWeight += options[i].weight;
    }
    int picked = Math::randint(1, totalWeight);
    SLCmove result = NONE;
    for (int i = 0; i < 8; ++i) {
        picked -= options[i].weight;
        if (picked <= 0) {
            result = options[i].move;
            break;
        }
    }
    return result;
}

SLCmove SLC::getMove() const {
    return move;
}

void SLC::update(std::vector<std::shared_ptr<Player>> players) {
    updatePlayers(players);
    move = NONE;
    if (newPlayer) {
        //move = getOption();
        move = FORWARD_3;
        switch (move) {
            case BACK_3: {
                newPlayer->setPosition(square_pos - 3);
                break;
            }
            case BACK_2: {
                newPlayer->setPosition(square_pos - 2);
                break;
            }
            case BACK_1: {
                newPlayer->setPosition(square_pos - 1);
                break;
            }
            case FORWARD_1: {
                newPlayer->setPosition(square_pos + 1);
                break;
            }
            case FORWARD_2: {
                newPlayer->setPosition(square_pos + 2);
                break;
            }
            case FORWARD_3: {
                newPlayer->setPosition(square_pos + 3);
                break;
            }
            case GO_TO_DCtims: {
                newPlayer->setPosition(10);
                break;
            }
            case GO_TO_COSAP: {
                newPlayer->setPosition(0);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void SLC::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    switch (move) {
            case BACK_3: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move back by 3 squares. ");
                break;
            }
            case BACK_2: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move back by 2 squares. ");
                break;
            }
            case BACK_1: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move back by 1 squares. ");
                break;
            }
            case FORWARD_1: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move forward by 1 squares. ");
                break;
            }
            case FORWARD_2: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move forward by 2 squares. ");
                break;
            }
            case FORWARD_3: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to move forward by 3 squares. ");
                break;
            }
            case GO_TO_DCtims: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to go to DC tims line. ");
                break;
            }
            case GO_TO_COSAP: {
                gfx->addMsg(newPlayer->getName() + " arrived at SLC and was asked to go to Collect OSAP. ");
                break;
            }
            default: {
                break;
            }
    }
}


