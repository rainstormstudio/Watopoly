#ifndef GOOSE_NESTING_H
#define GOOSE_NESTING_H

#include "../nonProperty.h"

class GooseNesting : public NonProperty {

public:
    GooseNesting(unsigned int square_pos, Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
