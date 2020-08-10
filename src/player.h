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

    void setPosition(unsigned int pos);
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
    void AddBalance(int total);
    void DecBalance(int total, char oweWhom);
};

#endif
