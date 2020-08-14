#include "DCtims.h"

DCtims::DCtims(unsigned int square_pos, Vec2 coord, std::string name)
    : NonProperty(square_pos, coord, name) {
    currentPlayer = 0;
}

void DCtims::setCurrentPlayer(unsigned int current) {
    currentPlayer = current;
}

void DCtims::update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) {
    updatePlayers(players);
    if (newPlayer) {
        if (newPlayer->getTimsTurn() == 0) {
            gfx->addMsg(newPlayer->getName() + " arrived at DC Tims. ");
        }
    }
    if (!newPlayer && players[currentPlayer]->getTimsTurn() > 0) {
        gfx->addMsg("You are currently in the DC Tims Line. \n");
        gfx->addMsg("You have following options to choose from:\n");
        gfx->addMsg("    1. roll two dice (You can leave the line if you roll doubles)\n");
        gfx->addMsg("    2. pay $50\n");
        gfx->addMsg("    3. use your Roll Up the Rim cup. (You currently have " + std::to_string(players[currentPlayer]->getTimsCups()) + ")");
    }
}

void DCtims::render(std::shared_ptr<Graphics> gfx) {
    gfx->write(name, coordinate.x, coordinate.y, 8);
    for (unsigned int i = 0; i < players.size(); ++i) {
        gfx->draw(players[i]->getSymbol(), coordinate.x + i, coordinate.y + 3);
    }
}

