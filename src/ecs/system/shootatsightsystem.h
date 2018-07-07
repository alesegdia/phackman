#pragma once

#include <secs/entitysystem.h>

#include "../components.h"

class ShootAtSightSystem : public secs::TypedEntitySystem<AgentInputComponent, ShootAtSightComponent, MapAwarenessComponent>
{
public:

    void process( double delta, const secs::Entity& e, AgentInputComponent& aic, ShootAtSightComponent& sc, MapAwarenessComponent& mac )
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(sc);
        bool detected = false;
        for( int i = 0; i < 4; i++ )
        {
            Facing f = (Facing)i;
            bool sensor_status = mac.getDirectionSensor(0, f);
            if( true == sensor_status )
            {
                detected = true;
                attackToDirection( f, aic );
                auto& ssc = component<ShootComponent>(e);
                ssc.facing = f;
                break;
            }
        }

        if( detected == false )
        {
            aic.requestedAttack = false;
        }
    }

private:
    void attackToDirection( Facing f, AgentInputComponent& aic )
    {
        aic.inputRequested = true;
        aic.requestedAttack = true;
        aic.requestedFacing = f;

    }

};


