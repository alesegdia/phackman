#pragma once

#include <secs/secs.h>
#include "../components.h"

class Damage : public secs::TypedEntitySystem<HealthComponent, DamageComponent>
{
public:
	void process( double delta, const secs::Entity& e, HealthComponent& healthcomponent, DamageComponent& damagecomponent )
	{
	
	}
};	

