#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "../building.h"

class Residence : public Building {
public:
    Residence(unsigned int pos, std::string name, unsigned int cost);

    // Rent is calculated based on the number of residences a player owns
    unsigned int getRent() const;

    void notify(std::shared_ptr<Player> player) override;
};

#endif
