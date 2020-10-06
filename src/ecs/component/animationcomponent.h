#pragma once

#include <aether/aether.h>

struct AnimationComponent
{
    std::shared_ptr<aether::graphics::Animation> animation;
    aether::graphics::AnimationData animationData;
};
