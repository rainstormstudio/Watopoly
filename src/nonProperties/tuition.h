#ifndef TUITION_H
#define TUITION_H

#include "../nonProperty.h"

class Tuition : public NonProperty {
public:
    Tuition(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
