#pragma once

#include "../../ai/pfmap.h"

struct MapAgentStateComponent
{
	PathNode::SharedPtr lastNode;
	PathNode::SharedPtr targetNode;
};
