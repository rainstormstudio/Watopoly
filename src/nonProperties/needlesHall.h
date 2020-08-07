#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H

#include "../nonProperty.h"

class NeedlesHall : public NonProperty {
public:
    NeedlesHall(Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
