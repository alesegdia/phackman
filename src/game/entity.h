#pragma once

#include "../core/animation.h"
#include "assets.h"

struct Entity
{
	float x = 0;
	float y = 0;
	std::shared_ptr<Animation> anim = nullptr;
	AnimationData animData;
};
