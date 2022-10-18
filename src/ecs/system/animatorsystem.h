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

        aether::graphics::Animation::SharedPtr newAnim = nullptr;

        newAnim = antr_comp.stand_animation;

        if( agtinput_comp.inputRequested )
		{
            newAnim = antr_comp.walk_animation;
		}

        if( agtinput_comp.requestedAttack )
		{
            newAnim = antr_comp.attack_animation;
		}

        if( agtinput_comp.inputRequested && agtinput_comp.requestedDesinfect )
        {
            newAnim = antr_comp.desinfect_walk_animation;
        }

        if( false == agtinput_comp.inputRequested && agtinput_comp.requestedDesinfect )
        {
            newAnim = antr_comp.desinfect_stand_animation;
        }

        if( newAnim != nullptr && newAnim != anim_comp.animation )
        {
            anim_comp.animation = newAnim;
            anim_comp.animation->Reset(anim_comp.animationData);
        }

	}

};
