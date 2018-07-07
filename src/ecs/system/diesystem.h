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
        SECS_UNUSED(dc);
        if( hasComponent<OnDeathActionComponent>(e) )
        {
            auto& odac = component<OnDeathActionComponent>(e);
            odac.action(e);
        }
        processor()->removeEntity(e);
    }
};
