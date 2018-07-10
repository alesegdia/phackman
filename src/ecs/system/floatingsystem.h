#pragma once

#include <secs/secs.h>
#include "../components.h"

class FloatingSystem : public secs::TypedEntitySystem<FloatingComponent, TransformComponent>
{
public:
	void process( double delta, const secs::Entity& e, FloatingComponent& floatingcomponent, TransformComponent& transformcomponent )
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        transformcomponent.position.y(transformcomponent.position.y() - floatingcomponent.speed);
	}
};	

