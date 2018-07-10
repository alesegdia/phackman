#pragma once

#include <secs/secs.h>
#include "../components.h"

class DisableShootWhenUnpoweredSystem : public secs::TypedEntitySystem<PowerConsumerComponent, ShootComponent>
{
public:
    void process( double delta, const secs::Entity &e, PowerConsumerComponent& powerconsumercomponent, ShootComponent& shootcomponent )
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        shootcomponent.force_disable = !powerconsumercomponent.powered;
	}
};	

