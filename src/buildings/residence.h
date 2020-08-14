#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "../building.h"

class Residence : public Building {
    unsigned int fee;
public:
    Residence(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost);

    // Rent is calculated based on the number of residences a player owns
    unsigned int getRent() const;

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
