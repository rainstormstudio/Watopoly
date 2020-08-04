#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H

#include "../nonProperty.h"

class NeedlesHall : public NonProperty {
public:
    NeedlesHall(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
