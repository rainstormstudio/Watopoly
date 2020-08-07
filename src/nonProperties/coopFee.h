#ifndef COOP_FEE_H
#define COOP_FEE_H

#include "../nonProperty.h"

class CoopFee : public NonProperty {
public:
    CoopFee(Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
