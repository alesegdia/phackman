#pragma once

#include <secs/secs.h>
#include "../components.h"

class DamageSystem : public secs::TypedEntitySystem<HealthComponent, DamageComponent>
{
public:
	void process( double delta, const secs::Entity& e, HealthComponent& healthcomponent, DamageComponent& damagecomponent )
	{
		if (damagecomponent.damageDone > 0)
		{
			damagecomponent.painTimer = 1000000;
		}
		if (damagecomponent.painTimer > 0)
		{
			damagecomponent.painTimer -= delta;
		}
		healthcomponent.currentHealth -= damagecomponent.damageDone;
		damagecomponent.damageDone = 0;
		//GetEntityProcessor()->RemoveComponent<DamageComponent>(e);
	}
};	

