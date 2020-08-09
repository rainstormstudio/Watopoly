#ifndef GO_TO_TIMS_H
#define GO_TO_TIMS_H

#include "../nonProperty.h"

class GoToTims : public NonProperty {
public:
    GoToTims(unsigned int square_pos, Vec2 coord, std::string name);

    std::string getType() override;

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
