#include "collectOSAP.h"

CollectOSAP::CollectOSAP(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {
}

void CollectOSAP::update(std::vector<std::shared_ptr<Player>> players) {
<<<<<<< HEAD
    this->players.clear();
    unsigned int OSAPFee = 200;
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getPosition() == square_pos) {
            players[i]->AddBalance(OSAPFee); // when player is on OSAP square, they receive $200
            this->players.push_back(players[i]);
        }
    }
=======
    updatePlayers(players);
>>>>>>> 9d5ee8c30b58c630855990b6f828dcd4c10d9958
}

void CollectOSAP::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}
