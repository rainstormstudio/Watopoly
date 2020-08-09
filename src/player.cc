#include "player.h"
#include "./buildings/academicBuilding.h"

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

double Player::getAsset() const { return asset; }

void Player::changeAsset(double c) { asset = c; }

void Player::mortgage(std::shared_ptr<Building> building) {
    if ((building->getOwner())->getName() != name) {
        std::cout << "Mortgage fails! You are not the owner of " << building->getName() << std::endl;
        return;
    }
    if (building->getMortgage() == true) {
        std::cout << "Mortgage is already activated!" << std::endl;
        return;
    }
    if (building->getType() == "Academic") {
        std::shared_ptr<Academics> academic = std::dynamic_pointer_cast<Academics>(building);
        if (academic->getImprovement() != 0) {
            std::cout << "Mortgage fails! Need to sell improvements before activating mortgage!" << std::endl;
            return;
        }
    }
    double mortgagedReceive = building->getCost()*0.5;
    // how to inform that no charge for other players when they pass by ?
    // decrease the asset from the current player
    asset -= building->getCost();
    balance += mortgagedReceive;
    building->setMortgage(true);
    std::cout << "Mortgage successfully! " << name << " have mortgaged " << building->getName()
    << ", and received $" << mortgagedReceive << "!" << std::endl;
}

void Player::setRolled(bool rolled) {
    hasRolled = rolled;
}
bool Player::rolled() const { return hasRolled; }

void Player::AddBalance(double total) {
    balance+=total;
}

void Player::DecBalance(double total, char oweWhom) {
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
