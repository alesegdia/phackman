#ifndef SHOOTCOMPONENT_H
#define SHOOTCOMPONENT_H

#include <functional>
#include <secs/secs.h>

struct ShootComponent
{
    float nextShotAvailable = 0;
    float rate = 1.f;
    float streak;
    std::function<void(const secs::Entity& e)> shoot;
};

#endif // SHOOTCOMPONENT_H
