#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

class Graphics;
class Building;

class Player {
    std::string name;
    char symbol;
    unsigned int position;
    int balance;
    unsigned int asset;

    unsigned int owedBank;
    bool canBuy;
    std::map<char, unsigned int> oweOtherPlayers;

    unsigned int numResi;
    unsigned int numGyms;
    unsigned int numTimsCups;

    bool isBankrupt;
    bool hasRolled;
    
public:
    Player(std::string name, char symbol);

    std::string getName() const;
    char getSymbol() const;

    void setPosition(int pos);
    unsigned int getPosition() const;

    void setGymNum(unsigned int num);
    unsigned int getGymNum() const;

    void setResiNum(unsigned int num);
    unsigned int getResiNum() const;

    unsigned int getAsset() const;
    void changeAsset(unsigned int c);

    void mortgage(std::shared_ptr<Building> building);
    void unmortgage(std::shared_ptr<Building> building);

    void setRolled(bool rolled);
    bool rolled() const;

    void setTimsCups(unsigned int num);
    unsigned int getTimsCups() const;

    void setBalance(int value);
    void addBalance(unsigned int total);
    void decBalance(unsigned int total);
    void decBalance(unsigned int total, char oweWhom);

    unsigned int getBalance() const;

    void setCanBuy(bool value);
    bool getCanBuy() const;
};

#endif
