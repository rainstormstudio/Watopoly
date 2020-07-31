#ifndef GO_TO_TIMS_H
#define GO_TO_TIMS_H

#include "../nonProperty.h"

class GoToTims : public NonProperty {
public:
    GoToTims(unsigned int pos, std::string name);

    void notify(std::shared_ptr<Player> player) override;
};

#endif
