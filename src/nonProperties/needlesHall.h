#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H

#include "../nonProperty.h"

class NeedlesHall : public NonProperty {
    int deltaMoney;
public:
    NeedlesHall(unsigned int square_pos, Vec2 coord, std::string name);

    int getOption();

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
