#pragma once

#include "../../core/facing.h"

struct AgentInputComponent
{
	Facing requestedFacing;
	bool inputRequested = true;
    float speed = 0;
	float lowest_speed = 10;
	float low_speed = 10;
	float normal_speed = 100;
	float fast_speed = 150;
	float normallow_speed = 80;
	bool requestedAttack = false;
    bool requestedDesinfect = false;
    bool requestedReinforce = false;
    bool carryCrucible = false;
    bool blockInfect = false;

};
