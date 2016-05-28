#pragma once

#include <memory>

#include <alligator/graphics/animation.h>
#include "../core/facing.h"
#include "../core/geometry.h"
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
	void setRequestedFacing( Facing dir );
	void setEnableMovement( bool enable );

private:

	void handleMovement(double delta);

	static constexpr bool ENABLE_DEBUG = false;

	bool m_canMove = true;
	vec2 m_position;
	float m_speed = 60;
	Animation::SharedPtr m_anim = nullptr;
	NavigationMap::SharedPtr m_navmap;
	AnimationData m_animData;
	Facing m_facing = Facing::Right;
	Facing m_requestedFacing = Facing::Right;
	PathNode::SharedPtr m_lastNode = nullptr;
	PathNode::SharedPtr m_targetNode = nullptr;

};
