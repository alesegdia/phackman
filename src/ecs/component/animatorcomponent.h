#pragma once

#include <alligator/graphics/animation.h>

struct AnimatorComponent
{
	Animation::SharedPtr stand_animation = nullptr;
	Animation::SharedPtr walk_animation = nullptr;
    Animation::SharedPtr attack_animation = nullptr;
    Animation::SharedPtr desinfect_walk_animation = nullptr;
    Animation::SharedPtr desinfect_stand_animation = nullptr;
};
