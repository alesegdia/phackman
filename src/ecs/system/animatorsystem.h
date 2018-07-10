#pragma once

#include <secs/secs.h>
#include "../components.h"

class AnimatorSystem : public secs::TypedEntitySystem<
        AgentInputComponent,
        AnimationComponent,
        AnimatorComponent>
{
public:
    void process(double delta, const secs::Entity &e,
                 AgentInputComponent& agtinput_comp,
                 AnimationComponent& anim_comp,
                 AnimatorComponent& antr_comp) override
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);

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

        if( agtinput_comp.inputRequested && agtinput_comp.requestedDesinfect && antr_comp.desinfect_walk_animation )
        {
            anim_comp.animation = antr_comp.desinfect_walk_animation;
        }

        if( false == agtinput_comp.inputRequested && agtinput_comp.requestedDesinfect && antr_comp.desinfect_stand_animation )
        {
            anim_comp.animation = antr_comp.desinfect_stand_animation;
        }
	}
};
