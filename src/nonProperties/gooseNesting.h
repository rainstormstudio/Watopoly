#ifndef GOOSE_NESTING_H
#define GOOSE_NESTING_H

#include "../nonProperty.h"

class GooseNesting : public NonProperty {
public:
    GooseNesting(unsigned int pos, std::string name);

    void notify(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
