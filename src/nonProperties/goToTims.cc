#include "goToTims.h"

GoToTims::GoToTims(unsigned int square_pos, Vec2 coord, std::string name) 
	: NonProperty(square_pos, coord, name) {}

void GoToTims::update(std::vector<std::shared_ptr<Player>> players) {
	for (unsigned int i = 0; i < this->players.size(); i++) {
		this->players[i] = nullptr;
	}

	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i]->getPosition() == this->square_pos) {
			players[i]->setPosition(10);
		}
	}
}

void GoToTims::render(std::shared_ptr<Graphics> gfx) {
	int len = name.length();
	for (int i = 0; i < len; ++i) {
		gfx->draw(name[i], coordinate.x + i, coordinate.y + 2);
	}
}