#pragma once

#include <secs/secs.h>
#include "../components.h"

class DeathCountdownSystem : public secs::TypedEntitySystem<DeathTimerComponent>
{
public:
    void process( double delta, const secs::Entity& e, DeathTimerComponent& deathtimercomponent )
	{
        deathtimercomponent.ttl -= delta;
        if( deathtimercomponent.ttl < 0 )
        {
            processor()->removeEntity(e);
        }
	}
};	

