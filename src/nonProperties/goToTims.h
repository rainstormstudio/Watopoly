#ifndef GO_TO_TIMS_H
#define GO_TO_TIMS_H

#include "../nonProperty.h"

class GoToTims : public NonProperty {
public:
    GoToTims(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
