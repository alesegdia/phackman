#pragma once

#include <memory>

#include "../core/animation.h"
#include "../core/direction.h"
#include "assets.h"

class Entity
{
public:
	typedef std::shared_ptr<Entity> SharedPtr;

	Entity( float x, float y );

	virtual void update(double delta);
	void render();

protected:
	void setAnim( Animation::SharedPtr anim );
	void setFacing( Direction dir );

private:
	float m_x = 0;
	float m_y = 0;
	std::shared_ptr<Animation> m_anim = nullptr;
	float m_speed = 60;
	AnimationData m_animData;
	Direction m_facing = Direction::RIGHT;

};


class Player : public Entity
{
public:
	typedef std::shared_ptr<Player> SharedPtr;

	Player(float x, float y);

	void update(double delta) override;
};
