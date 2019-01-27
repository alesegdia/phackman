#pragma once

#include <aether/aether.h>

struct AnimationComponent
{
    aether::graphics::Animation::SharedPtr animation = nullptr;
    aether::graphics::AnimationData animationData;
};
