#pragma once

#include <secs/secs.h>
#include "../components.h"

class UnpoweredGraphicOverridingSystemSystem : public secs::TypedEntitySystem<PowerConsumerComponent, RenderComponent>
{
public:
    void process( double delta, const secs::Entity &e, PowerConsumerComponent& powerconsumercomponent, RenderComponent& rendercomponent )
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        auto graphic = powerconsumercomponent.unpowered_asset;
        if( graphic != nullptr && false == powerconsumercomponent.powered )
        {
            rendercomponent.bitmap = *powerconsumercomponent.unpowered_asset;
        }
	}
};	

