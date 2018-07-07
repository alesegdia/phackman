#pragma once

#include "../../core/facing.h"

struct AgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
    int speed = 100;
    int lower_speed = 20;
    int normal_speed = 100;
    bool requestedAttack = false;
    bool requestedDesinfect = false;
    bool requestedReinforce = false;
};
