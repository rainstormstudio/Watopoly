#include "player.h"

Player::Player(std::string name, char symbol)
    : name{name}, symbol{symbol} {}

std::string Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}

void Player::setPosition(unsigned int pos) {
    position = pos;
}

unsigned int Player::getPosition() const {
    return position;
}

unsigned int Player::getGymNum() const {
    return numGyms;
}

unsigned int Player::getResiNum() const {
    return numResi;
}

void Player::render(Graphics & gfx) {
    // show player on the graph
    return;
}


