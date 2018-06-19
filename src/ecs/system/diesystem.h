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
};
