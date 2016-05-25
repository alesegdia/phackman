#pragma once

#include <alligator/graphics/animation.h>

struct AnimationComponent
{
	Animation* animation = nullptr;
	AnimationData animationData;
};
