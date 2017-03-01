#pragma once

#include <secs/secs.h>
#include "../component/components.h"

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

	void process( float delta, const secs::Entity &e ) override
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

