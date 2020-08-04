#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "square.h"
#include "types.h"

class NonProperty : public Square {
public:
    NonProperty(unsigned int pos, std::string name);
    
    void notify(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;

};

#endif
