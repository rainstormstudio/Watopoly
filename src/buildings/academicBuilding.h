#ifndef ACADEMIC_BUILDING_H
#define ACADEMIC_BUILDING_H

#include "../building.h"

class Academics : public Building {
    unsigned int improvementCost;
    unsigned int tuitions[6];
    unsigned int improvement;
public:
    Academics(unsigned int pos, std::string name, unsigned int cost,
              unsigned int improvementCost, 
              unsigned int tuition_0, unsigned int tuition_1, 
              unsigned int tuition_2, unsigned int tuition_3,
              unsigned int tuition_4, unsigned int tuition_5);
    
    unsigned int getTuition(unsigned int index) const;
    unsigned int getImprovementCost() const;

    unsigned int getImprovement() const;
    
    void notify(std::shared_ptr<Player> player) override;

    void render(Graphics & gfx) override;
};

#endif
