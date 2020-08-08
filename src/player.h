#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

class Graphics;
class Building;

class Player {
    std::string name;
    char symbol;
    unsigned int position;
    unsigned int balance;
    unsigned int owedBank;
    std::map<char, unsigned int> oweOtherPlayers;

    unsigned int numResi;
    unsigned int numGyms;

    bool isBankrupt;
    bool hasRolled;
    
public:
    Player(std::string name, char symbol);

    std::string getName() const;
    char getSymbol() const;

    void setPosition(unsigned int pos);
    unsigned int getPosition() const;
    unsigned int getGymNum() const;
    unsigned int getResiNum() const;

    void setRolled(bool rolled);
    bool rolled() const;

    void AddBalance(unsigned int total);
    void DecBalance(unsigned int total, char oweWhom);
};

#endif
