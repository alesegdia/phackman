#pragma once

#include <secs/secs.h>
#include <cmath>
#include "../components.h"

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2

/**
 * @brief The FacingRenderingSystem updates changes TransformComponent angle
 * depending on RenderFacingComponent.
 */
class FacingRenderingSystem : public secs::TypedEntitySystem< TransformComponent, RenderFacingComponent >
{
public:
    void process( double delta, const secs::Entity &e,
                  TransformComponent& transformcomponent,
                  RenderFacingComponent& renderfacingcomponent ) override
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        switch( renderfacingcomponent.facing )
		{
        case Facing::Up:	transformcomponent.angle = 0; break;
        case Facing::Down:	transformcomponent.angle = M_PI; break;
        case Facing::Right:	transformcomponent.angle = M_PI_2; break;
        case Facing::Left:	transformcomponent.angle = -M_PI_2; break;
        default: break;
		}

	}
};

