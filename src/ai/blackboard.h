#pragma once

#include "pfmap.h"

class Blackboard
{
public:
	static Blackboard instance;

	NavigationMap::SharedPtr navigationMap;

private:
	Blackboard()
	{

	}

};
