#pragma once

#include <aether/aether.h>

struct TileComponent
{
    aether::math::Vec2i current = aether::math::Vec2i(0, 0);
    aether::math::Vec2i previous = aether::math::Vec2i(0, 0);
};
