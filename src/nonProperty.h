#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "square.h"
#include "types.h"

class NonProperty : public Square {
public:
    NonProperty(unsigned int square_pos, Vec2 coord, std::string name);
    
    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;

};

#endif
