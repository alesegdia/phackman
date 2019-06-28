#pragma once

#include "../../core/facing.h"

struct AgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
    float speed = 0;
    float lower_speed = 20;
    float normal_speed = 100;
    bool requestedAttack = false;
    bool requestedDesinfect = false;
    bool requestedReinforce = false;
};
