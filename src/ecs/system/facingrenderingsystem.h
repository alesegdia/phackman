#pragma once

#include <secs/secs.h>
#include <cmath>
#include "../component/components.h"

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2

/**
 * @brief The FacingRenderingSystem updates changes TransformComponent angle
 * depending on RenderFacingComponent.
 */
class FacingRenderingSystem : public secs::EntitySystem
{
public:

	FacingRenderingSystem( secs::Engine& world )
		: m_engine(world)
	{
		setNeededComponents<TransformComponent, RenderFacingComponent>();
	}

    void process( double delta, const secs::Entity &e ) override
	{
		auto& transform_comp = m_engine.component<TransformComponent>(e);
		auto& facing_comp = m_engine.component<RenderFacingComponent>(e);

		switch( facing_comp.facing )
		{
		case Facing::Up:	transform_comp.angle = 0; break;
		case Facing::Down:	transform_comp.angle = M_PI; break;
		case Facing::Right:	transform_comp.angle = M_PI_2; break;
		case Facing::Left:	transform_comp.angle = -M_PI_2; break;
		}

	}

private:
	secs::Engine& m_engine;

};

