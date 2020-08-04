#ifndef GYM_H
#define GYM_H

#include "../building.h"

class Gym : public Building {
public:
    // Usage fees are calculated by rolling two dice
    unsigned int getUsageFee() const;
    
    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
