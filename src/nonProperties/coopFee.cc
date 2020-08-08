#include "coopFee.h"

CoopFee::CoopFee(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {}

void CoopFee::update(std::vector<std::shared_ptr<Player>> players) {
    this->players.clear();
    unsigned int CoopFee = 150;
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i]->getPosition() == square_pos) {
            //players[i]->DecBalance(CoopFee, players[i]->getSymbol());
            this->players.push_back(players[i]);
        }
    }
}

void CoopFee::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }

	for (unsigned int i = 0; i < players.size(); i++) {
		gfx->addMsg(players[i]->getName() + " paid the co-op fee!");
	}
}
