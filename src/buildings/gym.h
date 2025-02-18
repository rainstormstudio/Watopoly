#ifndef GYM_H
#define GYM_H

#include "../building.h"

class Gym : public Building {
    unsigned int fee;
public:
    Gym(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost);
    
    // Usage fees are calculated by rolling two dice
    unsigned int getUsageFee() const;

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
