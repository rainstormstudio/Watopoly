#ifndef DCTIMS_H
#define DCTIMS_H

#include "../nonProperty.h"

class DCtims : public NonProperty {
public:
    DCtims(Vec2 coord, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
