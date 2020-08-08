#include "gooseNesting.h"

GooseNesting::GooseNesting(unsigned int square_pos, Vec2 coord, std::string name)
	: NonProperty(square_pos, coord, name) {}

void GooseNesting::update(std::vector<std::shared_ptr<Player>> players) {
	this->players.clear();
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i]->getPosition() == this->square_pos)
			this->players.push_back(players[i]);
	}
}

void GooseNesting::render(std::shared_ptr<Graphics> gfx) {
	gfx->write(name, coordinate.x, coordinate.y, 8);
	for (unsigned int i = 0; i < players.size(); ++i) {
		gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
	}
	
	for (unsigned int i = 0; i < players.size(); i++) {
		gfx->addMsg(players[i]->getName() + " is attacked by a flock of nesting geese.");
	}
}