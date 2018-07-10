#ifndef SHOOTINGSYSTEM_H
#define SHOOTINGSYSTEM_H

#include <secs/entitysystem.h>

#include "../components.h"

class ShootingSystem : public secs::TypedEntitySystem<AgentInputComponent, ShootComponent>
{
public:

    void process( double delta, const secs::Entity &e, AgentInputComponent& aic, ShootComponent& sc )
    {
        if( sc.nextShotAvailable > 0 )
        {
            sc.nextShotAvailable -= delta;
        }
        if( aic.requestedAttack && sc.nextShotAvailable <= 0 && sc.force_disable == false )
        {
            processor()->addComponent<TriggerComponent>(e);
            sc.nextShotAvailable = sc.rate;
        }
    }
};

#endif // SHOOTINGSYSTEM_H
