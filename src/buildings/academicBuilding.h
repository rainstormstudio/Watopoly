#ifndef ACADEMIC_BUILDING_H
#define ACADEMIC_BUILDING_H

#include "../building.h"

class Academics : public Building {
    std::string block;
    unsigned int improvementCost;
    unsigned int tuitions[6];
    unsigned int improvement;
public:
    Academics(Vec2 coord, std::string name, unsigned int cost,
              std::string block, unsigned int improvementCost, 
              unsigned int tuition_0, unsigned int tuition_1, 
              unsigned int tuition_2, unsigned int tuition_3,
              unsigned int tuition_4, unsigned int tuition_5);
    
    std::string getBlock() const;
    unsigned int getTuition(unsigned int index) const;
    unsigned int getImprovementCost() const;

    unsigned int getImprovement() const;
    
    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
