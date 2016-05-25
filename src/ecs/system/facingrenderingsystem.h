#pragma once

#include <secs/secs.h>
#include "../component/components.h"

class FacingRenderingSystem : public secs::EntitySystem
{
public:

	FacingRenderingSystem( secs::Engine& world )
		: m_world(world)
	{
		setNeededComponents<TransformComponent, FacingComponent>();
	}

	void process(const secs::Entity &e)
	{
		auto& transform_comp = m_world.component<TransformComponent>(e);
		auto& facing_comp = m_world.component<FacingComponent>(e);

		switch( facing_comp.facing )
		{
		case FacingComponent::Facing::Up:		transform_comp.angle = 0; break;
		case FacingComponent::Facing::Down:		transform_comp.angle = M_PI; break;
		case FacingComponent::Facing::Left:		transform_comp.angle = M_PI_2; break;
		case FacingComponent::Facing::Right:	transform_comp.angle = -M_PI_2; break;
		}

	}

private:
	secs::Engine& m_world;

};
