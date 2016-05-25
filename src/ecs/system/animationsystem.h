#pragma once

#include <secs/secs.h>
#include "../component/components.h"


class AnimationSystem : public secs::EntitySystem
{
public:

	AnimationSystem( secs::Engine& world )
		: m_world(world)
	{
		setNeededComponents<RenderComponent, AnimationComponent>();
	}

	void process(const secs::Entity &e)
	{
		auto& render_comp = m_world.component<RenderComponent>(e);
		auto& anim_comp = m_world.component<AnimationComponent>(e);

		anim_comp.animationData.timer += 0.1f;
		anim_comp.animation->updateData( anim_comp.animationData );
		render_comp.bitmap = anim_comp.animationData.currentFrame;
	}

private:
	secs::Engine& m_world;

};