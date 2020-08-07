#ifndef COLLECT_OSAP_H
#define COLLECT_OSAP_H

#include "../nonProperty.h"

class CollectOSAP : public NonProperty {
public:
    CollectOSAP(Vec2 coord, std::string name);

    void update(std::vector<std::shared_ptr<Player>> players) override;

    void render(std::shared_ptr<Graphics> gfx) override;
};

#endif
