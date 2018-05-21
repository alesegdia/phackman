#pragma once

#include "../../ai/pfmap.h"

struct AgentMapStateComponent
{
	PathNode::SharedPtr lastNode;
	PathNode::SharedPtr targetNode;
};
