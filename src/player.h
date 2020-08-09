#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

class Graphics;
class Building;

class Player {
    std::string name;
    char symbol;
    unsigned int position;
    double balance;
    double asset;

    double owedBank;
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

    double getAsset() const;
    void changeAsset(double c);

    void mortgage(std::shared_ptr<Building> building);
    void unmortgage(std::shared_ptr<Building> building);

    void setRolled(bool rolled);
    bool rolled() const;

    void AddBalance(double total);
    void DecBalance(double total, char oweWhom);
};

#endif
