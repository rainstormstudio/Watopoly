#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "square.h"
#include "types.h"
#include "math.h"

class NonProperty : public Square {
public:
    NonProperty(unsigned int square_pos, Vec2 coord, std::string name);

    //void setMortgage() override;

    //void removeMortgage() override;

    std::string getOwnerName() override;

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;

};

#endif
