#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include <secs/secs.h>

#include "../components.h"

class TriggerSystem : public secs::TypedEntitySystem<TriggerComponent, ShootComponent>
{
public:

    void process( double delta, const secs::Entity &e, TriggerComponent& tc, ShootComponent& sc )
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(tc);
        GetEntityProcessor()->RemoveComponent<TriggerComponent>(e);
        sc.shoot(e);
    }

};

#endif // TRIGGERSYSTEM_H
