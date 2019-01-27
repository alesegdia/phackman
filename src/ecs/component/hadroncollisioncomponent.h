#pragma once

#include <hadron/hadron.h>

#include <aether/aether.h>

struct HadronCollisionComponent
{
    aether::math::Vec2f offset = aether::math::Vec2f(0,0);
    hadron::Body* body = nullptr;
};
