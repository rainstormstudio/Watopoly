#include "player.h"
#include "./buildings/academicBuilding.h"
#include "./buildings/gym.h"
#include "./buildings/residence.h"

Player::Player(std::string name, char symbol)
	: name{name}, symbol{symbol}, position{0}, balance{1500}, asset{0}, owedMoney{0}, numResi{0}, numGyms{0}, numTimsCups{0} {
    hasRolled = false;
    isBankrupt = false;
    willBankrupt = false;
    canBuy = false;
    owedPlayer = nullptr;
    timsTurn = 0;
}

std::string Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}

void Player::setPosition(int pos) {
    if (pos < 0) {
        pos = 40 + pos;
    }
    if (pos >= 40) {
        pos = pos % 40;
    }
    position = pos;
}

unsigned int Player::getPosition() const {
    return position;
}

void Player::setGymNum(unsigned int num) {
    numGyms = num;
}

unsigned int Player::getGymNum() const {
    return numGyms;
}

void Player::setResiNum(unsigned int num) {
    numResi = num;
}

unsigned int Player::getResiNum() const {
	return numResi;
}

unsigned int Player::getAsset() const { return asset; }

void Player::changeAsset(unsigned int c) { asset = c; }

bool Player::mortgage(std::shared_ptr<Building> building) {
    if (building->getOwner() == nullptr || (building->getOwner())->getName() != name) {
        std::cout << "Mortgage fails! You are not the owner of " << building->getName() << "!" << std::endl;
        return false;
    }
    if (building->getMortgage() == true) {
        std::cout << "Mortgage is already activated!" << std::endl;
        return false;
    }
    std::shared_ptr<Academics> academic = std::dynamic_pointer_cast<Academics>(building);
    if (academic) {        
        if (academic->getImprovement() != 0) {
            std::cout << "Mortgage fails! Need to sell improvements before activating mortgage!" << std::endl;
            return false;
        }
    }
    unsigned int mortgagedReceive = building->getCost()*0.5;
    // how to inform that no charge for other players when they pass by ?
    // decrease the asset from the current player
    asset -= building->getCost();
    balance += mortgagedReceive;
    building->setMortgage(true);
    return true;
}

bool Player::unmortgage(std::shared_ptr<Building> building) {
    if (building->getOwner() == nullptr || (building->getOwner())->getName() != name) {
        std::cout << "Unmortgage fails! You are not the owner of " << building->getName() << "!" << std::endl;
        return false;
    }
    if (building->getMortgage() == false) {
        std::cout << "Unmortgage is already activated!" << std::endl;
        return false;
    }
    unsigned int pay = building->getCost()*0.6;
    // how to inform that no charge for other players when they pass by ?
    // decrease the asset from the current player
    if (pay > balance) {
        std::cout << "Unmortgage fails! Do not have enough balance for unmortgage!" << std::endl;
        return false;
    } else {
        asset += building->getCost();
        building->setMortgage(false);
        balance -= pay;
    }
    return true;
}

void Player::setRolled(bool rolled) {
    hasRolled = rolled;
}
bool Player::rolled() const { return hasRolled; }

void Player::setTimsCups(unsigned int num) {
    numTimsCups = num;
}

unsigned int Player::getTimsCups() const { return numTimsCups; }

void Player::setBalance(unsigned int value) {
    balance = value;
}

void Player::addBalance(unsigned int total) {
    balance += total;
}

void Player::decBalance(unsigned int total, std::shared_ptr<Player> owedPlayer) {
    if (balance < total) {
        willBankrupt = true;
        owedMoney = total - balance;
        balance = 0;
        this->owedPlayer = owedPlayer;
    } else {
        balance -= total;
    }
}

unsigned int Player::getBalance() const { return balance; }

void Player::setNeedToPayTuition(bool value) {
    NeedToPayTuition = value;
}

bool Player::getNeedToPayTuition() const {
    return NeedToPayTuition;
}

int Player::payTuition(std::string option) {
    if (option == "1") {
        decBalance(300, nullptr);
        if (!willBankrupt) {
            std::cout << "Successfully paid $300 tuition fees!" << std::endl;
        }
        return 300;
    }
    if (option == "2") {
        int totalWorth = asset+balance;
        decBalance(static_cast<unsigned int>(totalWorth*0.1), nullptr);
        if (!willBankrupt) {
            std::cout << "Successfully paid $" << totalWorth*0.1 << " tuition fees!" << std::endl;
        }
        return totalWorth*0.1;
    }
    return 0;
}

void Player::setNeedToCoopFee(bool value) {
    NeedToCoopFee = value;
}

bool Player::getNeedToCoopFee() const {
    return NeedToCoopFee;
}

void Player::setCollectGooseBonus(bool value) {
    collectGooseBonus = value;
}

bool Player::getCollectGooseBonus() const {
    return collectGooseBonus;
}

void Player::setPassOSAP(bool value) {
    passOSAP = value;
}

bool Player::getPassOSAP() const {
    return passOSAP;
}

void Player::setLandOSAP(bool value) {
    landOSAP = value;
}

bool Player::getLandOSAP() const {
    return landOSAP;
}

void Player::setCanBuy(bool value) {
    canBuy = value;
}

bool Player::getCanBuy() const {
    return canBuy;
}

void Player::buy(std::shared_ptr<Building> building) {
    unsigned int cost = building->getCost();
    balance -= cost;
    asset += cost;
    if (std::dynamic_pointer_cast<Gym>(building)) {
        numGyms += 1;
    }
    if (std::dynamic_pointer_cast<Residence>(building)) {
        numResi += 1;
    }
}

void Player::gotoTims() {
    position = 10;
    timsTurn = 1;
    teleported = true;
}

void Player::setTimsTurn(unsigned int value) {
    timsTurn = value;
}

unsigned int Player::getTimsTurn() const {
    return timsTurn;
}

void Player::resetTimsTurn() {
    timsTurn = 0;
}

bool Player::getBankruptcy() const {
    return isBankrupt;
}

void Player::setBankruptcy(bool value) {
    isBankrupt = value;
}

bool Player::getWillBankrupt() const {
    return willBankrupt;
}

void Player::setWillBankrupt(bool value) {
    willBankrupt = value;
}

std::shared_ptr<Player> Player::getOwedPlayer() const { return owedPlayer; }

unsigned int Player::getOwedMoney() const {
    return owedMoney;
}

void Player::setOwedMoney(unsigned int value) {
    owedMoney = value;
}

bool Player::getTeleported() const { return teleported; }

void Player::setTeleported(bool value) { teleported = value; }
