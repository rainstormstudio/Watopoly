#include "goToTims.h"

GoToTims::GoToTims(unsigned int square_pos, Vec2 coord, std::string name) 
	: NonProperty(square_pos, coord, name) {}

void GoToTims::update(std::vector<std::shared_ptr<Player>> players) {
	this->players.clear();

	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i]->getPosition() == this->square_pos) {
			players[i]->setPosition(10);
		}
	}
}

void GoToTims::render(std::shared_ptr<Graphics> gfx) {
	gfx->write(name, coordinate.x, coordinate.y, 8);
	for (unsigned int i = 0; i < players.size(); ++i) {
		gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
	}
}