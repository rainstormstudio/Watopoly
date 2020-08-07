#include "gooseNesting.h"

GooseNesting::GooseNesting(unsigned int square_pos, Vec2 coord, std::string name)
	: NonProperty(square_pos, coord, name) {}

void GooseNesting::update(std::vector<std::shared_ptr<Player>> players) {
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i] == this->square_pos)
			attacked_names.push_back(players[i]->getName());
	}
}

void GooseNesting::render(std::shared_ptr<Graphics> gfx) {
	int len = name.length();
	for (int i = 0; i < len; ++i) {
		gfx->draw(name[i], coordinate.x + i, coordinate.y + 2);
	}
	
	for (unsigned int = 0; i < attacked_names.size(); i++) {
		gfx->addMsg(attacked_players[i] + " is attacked by a flock of nesting geese.");
	}
}