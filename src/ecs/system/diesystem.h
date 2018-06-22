#pragma once

#include <secs/secs.h>

#include "../component/components.h"

class DieSystem : public secs::TypedEntitySystem<DieComponent>
{
public:
    void onAdded(const secs::Entity &e)
    {
        processor()->removeEntity(e);
    }

    void process(double delta, const secs::Entity &e, DieComponent &dc)
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        SECS_UNUSED(dc);
    }
};
