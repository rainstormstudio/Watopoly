#ifndef DCTIMS_H
#define DCTIMS_H

#include "../nonProperty.h"

class DCtims : public NonProperty {
public:
    DCtims(unsigned int pos, std::string name);

    void notify(std::shared_ptr<Player> player) override;
};

#endif
