#ifndef DCTIMS_H
#define DCTIMS_H

#include "../nonProperty.h"

class DCtims : public NonProperty {
public:
    DCtims(unsigned int square_pos, Vec2 coord, std::string name);

    std::string getType() override;

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
