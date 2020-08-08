#include "player.h"

Player::Player(std::string name, char symbol)
	: name{name}, symbol{symbol}, position{0}, balance{1500}, owedBank{0}, numResi{0}, numGyms{0} {
    hasRolled = false;
    isBankrupt = false;
    oweOtherPlayers = std::map<char, unsigned int> { {'G',0}, {'B',0}, {'D',0}, {'P',0},{'S',0},{'$',0},{'L',0},{'T',0} };
}

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

void Player::setRolled(bool rolled) {
    hasRolled = rolled;
}
bool Player::rolled() const { return hasRolled; }

void Player::AddBalance(unsigned int total) {
    balance+=total;
}

void Player::DecBalance(unsigned int total, char oweWhom) {
    if ((balance-total) < 0) {
        // should consider different cases here? To bank or other players?
        unsigned int totalOwe = total - balance;
        if (std::isblank(oweWhom)) {
            owedBank += totalOwe;
        } else {
            oweOtherPlayers.find(oweWhom)->second += totalOwe;
        }
    } else {
        balance -= total;
    }
}
