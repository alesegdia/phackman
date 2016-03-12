#pragma once

#include "entity.h"

class Player : public Entity
{
public:
	typedef std::shared_ptr<Player> SharedPtr;

	Player(float x, float y, NavigationMap::SharedPtr navmap);

	void update(double delta) override;
};
