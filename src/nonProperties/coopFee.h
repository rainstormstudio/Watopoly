#ifndef COOP_FEE_H
#define COOP_FEE_H

#include "../nonProperty.h"

class CoopFee : public NonProperty {
public:
    CoopFee(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
