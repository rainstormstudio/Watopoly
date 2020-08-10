#include "gooseNesting.h"

GooseNesting::GooseNesting(unsigned int square_pos, Vec2 coord, std::string name)
	: NonProperty(square_pos, coord, name) {}

std::string GooseNesting::getType() {
	return "NonProperty";
}

void GooseNesting::update(std::vector<std::shared_ptr<Player>> players) {
	updatePlayers(players);
}

void GooseNesting::render(std::shared_ptr<Graphics> gfx) {
	gfx->write(name, coordinate.x, coordinate.y, 7);
	for (unsigned int i = 0; i < players.size(); ++i) {
		gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
	}
	
	for (unsigned int i = 0; i < players.size(); i++) {
		gfx->addMsg(players[i]->getName() + " is attacked by a flock of nesting geese.");
	}
}