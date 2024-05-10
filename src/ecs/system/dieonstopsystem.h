#pragma once
#include <secs/secs.h>

#include "../components.h"

class DieOnStopSystem : public secs::TypedEntitySystem<DieOnStopComponent, TransformComponent>
{
public:

    void process( double delta, const secs::Entity &e, DieOnStopComponent& dos, TransformComponent& tc )
    {
        SECS_UNUSED(delta);
        if( dos.last_x == tc.position.GetX() && dos.last_y == tc.position.GetY() )
        {
            if (!GetEntityProcessor()->HasComponent<DieComponent>(e))
            {
                GetEntityProcessor()->AddComponent<DieComponent>(e);
            }
            GetEntityProcessor()->RemoveComponent<DieOnStopComponent>(e);
        }
        dos.last_x = tc.position.GetX();
        dos.last_y = tc.position.GetY();
    }

};

