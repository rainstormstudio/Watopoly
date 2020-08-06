#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "square.h"
#include "types.h"

class NonProperty : public Square {
public:
    NonProperty(Vec2 coord, std::string name);
    
    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;

};

#endif
