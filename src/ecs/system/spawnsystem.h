#pragma once

#include <secs/secs.h>
#include "../components.h"

class SpawnSystem : public secs::TypedEntitySystem<SpawnComponent>
{
public:
	void process( double delta, const secs::Entity& e, SpawnComponent& spawncomponent )
	{
	
	}
};	

