#ifndef SHOOTINGSYSTEM_H
#define SHOOTINGSYSTEM_H

#include <secs/entitysystem.h>

#include "../component/components.h"

class ShootingSystem : public secs::TypedEntitySystem<TriggerComponent, ShootComponent>
{
public:
	ShootingSystem();

	void process( float delta, const secs::Entity &e, TriggerComponent& tc, ShootComponent& sc )
	{
		processor()->removeComponent<TriggerComponent>(e);
		sc.shoot(e);
	}
};

#endif // SHOOTINGSYSTEM_H
