#ifndef DCTIMS_H
#define DCTIMS_H

#include "../nonProperty.h"

class DCtims : public NonProperty {
public:
    DCtims(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
