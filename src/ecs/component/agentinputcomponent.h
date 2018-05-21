#pragma once

#include "../../core/facing.h"

struct AgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
    int speed = 100;
	bool requestedAttack = false;
};
