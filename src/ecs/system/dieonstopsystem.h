#pragma once
#include <secs/secs.h>

#include "../component/components.h"

class DieOnStopSystem : public secs::TypedEntitySystem<DieOnStopComponent, TransformComponent>
{
public:

    void process( double delta, const secs::Entity &e, DieOnStopComponent& dos, TransformComponent& tc )
    {
        if( dos.last_x == tc.position.x() && dos.last_y == tc.position.y() )
        {
            processor()->removeEntity(e);
        }
        dos.last_x = tc.position.x();
        dos.last_y = tc.position.y();
    }

};

