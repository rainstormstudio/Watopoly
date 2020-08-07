#ifndef SLC_H
#define SLC_H

#include "../nonProperty.h"

class SLC : public NonProperty {
public:
    SLC(Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
