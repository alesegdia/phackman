#pragma once

#include <hadron/hadron.h>

#include <alligator/alligator.h>

struct HadronCollisionComponent
{
    Vec2f offset = Vec2f(0,0);
    hadron::Body* body = nullptr;
};
