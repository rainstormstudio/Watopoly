#ifndef SLC_H
#define SLC_H

#include "../nonProperty.h"

class SLC : public NonProperty {
public:
    SLC(unsigned int pos, std::string name);

    void notify(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
