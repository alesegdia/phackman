#pragma once

struct BombComponent
{
	int64_t timeToLive = 1e6;
	bool explodedByContact = false;
	int numLives = 2;
};
