#ifndef BUILDING_H
#define BUILDING_H

#include "square.h"
#include "types.h"
#include "player.h"
#include "math.h"

class Building : public Square {
protected:
    unsigned int cost;
    std::shared_ptr<Player> owner;
    bool mortgaged;
public:
    Building(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost);

    std::shared_ptr<Player> getOwner() const;
    void setOwner(std::shared_ptr<Player> player);

    unsigned int getCost() const;

    bool getMortgage() const;

    void setMortgage(bool SetOrNot);

    void resetMortgage();

    std::string getOwnerName() override;

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;

};

#endif
