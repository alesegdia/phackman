#pragma once

#include <secs/secs.h>
#include "../component/components.h"

class AnimatorSystem : public secs::EntitySystem
{
public:

	AnimatorSystem(secs::Engine& world)
		: m_world(world)
	{
		setNeededComponents<AgentInputComponent, AnimationComponent, AnimatorComponent>();
	}

	void process(double delta, const secs::Entity &e) override
	{
		auto& agtinput_comp = m_world.component<AgentInputComponent>(e);
		auto& anim_comp = m_world.component<AnimationComponent>(e);
		auto& antr_comp = m_world.component<AnimatorComponent>(e);

		printf("%d\n", agtinput_comp.inputRequested);

		if (antr_comp.stand_animation != nullptr)
		{
			anim_comp.animation = antr_comp.stand_animation;
		}

		if( agtinput_comp.inputRequested && antr_comp.walk_animation != nullptr )
		{
			anim_comp.animation = antr_comp.walk_animation;
		}

		if( agtinput_comp.requestedAttack && antr_comp.attack_animation != nullptr )
		{
			anim_comp.animation = antr_comp.attack_animation;
		}
	}

private:
	secs::Engine& m_world;

};
