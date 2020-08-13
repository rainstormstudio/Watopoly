#ifndef SLC_H
#define SLC_H

#include "../nonProperty.h"

enum SLCmove {
    NONE,
    BACK_3,
    BACK_2,
    BACK_1,
    FORWARD_1,
    FORWARD_2,
    FORWARD_3,
    GO_TO_DCtims,
    GO_TO_COSAP
};

enum SLCmove;

class SLC : public NonProperty {
    SLCmove move;
public:
    SLC(unsigned int square_pos, Vec2 coord, std::string name);

    SLCmove getOption();

    SLCmove getMove() const;

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
