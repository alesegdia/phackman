#pragma once

#include <aether/aether.h>

struct AnimatorComponent
{
    aether::graphics::Animation::SharedPtr stand_animation = nullptr;
    aether::graphics::Animation::SharedPtr walk_animation = nullptr;
    aether::graphics::Animation::SharedPtr attack_animation = nullptr;
    aether::graphics::Animation::SharedPtr desinfect_walk_animation = nullptr;
	aether::graphics::Animation::SharedPtr desinfect_stand_animation = nullptr;
	aether::graphics::Animation::SharedPtr carry_crucible_walk_animation = nullptr;
	aether::graphics::Animation::SharedPtr carry_crucible_stand_animation = nullptr;
};

