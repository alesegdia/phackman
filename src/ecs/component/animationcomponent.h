#pragma once

#include <alligator/graphics/animation.h>

struct AnimationComponent
{
	Animation::SharedPtr animation = nullptr;
	AnimationData animationData;
};
