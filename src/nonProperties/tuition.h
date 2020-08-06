#ifndef TUITION_H
#define TUITION_H

#include "../nonProperty.h"

class Tuition : public NonProperty {
public:
    Tuition(Vec2 coord, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
