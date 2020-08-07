#ifndef GYM_H
#define GYM_H

#include "../building.h"

class Gym : public Building {
public:
    Gym(Vec2 coord, std::string name, unsigned int cost);
    
    // Usage fees are calculated by rolling two dice
    unsigned int getUsageFee() const;
    
    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
