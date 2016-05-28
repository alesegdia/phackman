#pragma once

#include "../../core/facing.h"

struct MapAgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
};
