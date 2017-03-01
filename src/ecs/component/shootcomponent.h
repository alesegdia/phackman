#ifndef SHOOTCOMPONENT_H
#define SHOOTCOMPONENT_H

#include <functional>
#include <secs/secs.h>

struct ShootComponent
{
	float rate;
	float streak;
	std::function<void(const secs::Entity& e)> shoot;
};

#endif // SHOOTCOMPONENT_H
