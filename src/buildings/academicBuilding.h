#ifndef ACADEMIC_BUILDING_H
#define ACADEMIC_BUILDING_H

#include "../building.h"

class Academics : public Building {
    std::string block;
    unsigned int improvementCost;
    unsigned int tuitions[6];
    unsigned int improvement = 0;
    unsigned int fee;
public:
    Academics(unsigned int square_pos, Vec2 coord, std::string name, unsigned int cost,
              std::string block, unsigned int improvementCost, 
              unsigned int tuition_0, unsigned int tuition_1, 
              unsigned int tuition_2, unsigned int tuition_3,
              unsigned int tuition_4, unsigned int tuition_5);
    
    std::string getBlock() const;
    unsigned int getTuition(unsigned int index) const;
    unsigned int getImprovementCost() const;

    void setImprovement(unsigned int value);
    unsigned int getImprovement() const;
    bool addImprovement();
    bool removeImprovement(); // bool so that we know whether successfully add or remove

    void update(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Graphics> gfx) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
