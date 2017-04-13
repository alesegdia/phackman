#pragma once

#include "../../core/facing.h"

struct MapAgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
    int speed = 10;
};
