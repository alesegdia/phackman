#pragma once

#include <memory>

#include "../core/animation.h"
#include "../core/direction.h"
#include "../ai/pfmap.h"
#include "assets.h"

class Entity
{
public:
	typedef std::shared_ptr<Entity> SharedPtr;

	Entity( float x, float y, NavigationMap::SharedPtr navmap );

	virtual void update(double delta);
	void render();

protected:
	void setAnim( Animation::SharedPtr anim );
	void setRequestedFacing( Direction dir );

private:
	float m_x = 0;
	float m_y = 0;
	float m_speed = 60;
	Animation::SharedPtr m_anim = nullptr;
	NavigationMap::SharedPtr m_navmap;
	AnimationData m_animData;
	Direction m_facing = Direction::RIGHT;
	Direction m_requestedFacing = Direction::RIGHT;
	PathNode::SharedPtr m_lastNode = nullptr;

};


class Player : public Entity
{
public:
	typedef std::shared_ptr<Player> SharedPtr;

	Player(float x, float y, NavigationMap::SharedPtr navmap);

	void update(double delta) override;
};
