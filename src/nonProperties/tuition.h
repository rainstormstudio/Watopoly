#ifndef TUITION_H
#define TUITION_H

#include "../nonProperty.h"

class Tuition : public NonProperty {
public:
    Tuition(unsigned int square_pos, Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
