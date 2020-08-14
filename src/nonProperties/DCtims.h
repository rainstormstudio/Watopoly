#ifndef DCTIMS_H
#define DCTIMS_H

#include "../nonProperty.h"

class DCtims : public NonProperty {
    unsigned int currentPlayer;
public:
    DCtims(unsigned int square_pos, Vec2 coord, std::string name);

    void setCurrentPlayer(unsigned int current);

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
