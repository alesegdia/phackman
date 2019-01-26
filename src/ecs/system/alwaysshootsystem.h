#pragma once

#include <secs/secs.h>
#include "../components.h"

class AlwaysShootSystem : public secs::TypedEntitySystem<AlwaysShootComponent, AgentInputComponent>
{
public:
	void process( double delta, const secs::Entity& e, AlwaysShootComponent& alwaysshootcomponent, AgentInputComponent& agentinputcomponent )
	{
        agentinputcomponent.requestedAttack = true;
	}
};	

