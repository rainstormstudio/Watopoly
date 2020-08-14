#include "gooseNesting.h"

GooseNesting::GooseNesting(unsigned int square_pos, Vec2 coord, std::string name)
	: NonProperty(square_pos, coord, name) {}

void GooseNesting::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
	updatePlayers(players);
	if (newPlayer) {
		newPlayer->setCollectGooseBonus(true);
		gfx->addMsg(newPlayer->getName() + " is attacked by a flock of nesting geese. ");
	}
}

void GooseNesting::render(std::shared_ptr<Graphics> gfx) {
	gfx->write(name, coordinate.x, coordinate.y, 7);
	for (unsigned int i = 0; i < players.size(); ++i) {
		gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
	}
}