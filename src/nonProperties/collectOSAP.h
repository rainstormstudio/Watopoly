#ifndef COLLECT_OSAP_H
#define COLLECT_OSAP_H

#include "../nonProperty.h"

class CollectOSAP : public NonProperty {
public:
    CollectOSAP(unsigned int pos, std::string name);

    void update(std::shared_ptr<Player> player) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
