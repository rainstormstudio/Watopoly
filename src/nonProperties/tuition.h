#ifndef TUITION_H
#define TUITION_H

#include "../nonProperty.h"

class Tuition : public NonProperty {
public:
    Tuition(unsigned int pos, std::string name);

    void notify(std::shared_ptr<Player> player) override;
};

#endif
