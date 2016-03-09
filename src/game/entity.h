#pragma once

#include <memory>

#include "../core/animation.h"
#include "assets.h"

class Entity
{
public:
	typedef std::shared_ptr<Entity> SharedPtr;

	Entity( float x, float y, std::shared_ptr<Animation> anim );

	void update(double delta);
	void render();

private:
	float m_x = 0;
	float m_y = 0;
	std::shared_ptr<Animation> m_anim = nullptr;
	AnimationData m_animData;

};
