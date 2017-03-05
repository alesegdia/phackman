#include "entityfactory.h"

EntityFactory::EntityFactory(secs::Engine &world)
	: m_world(world)
{

}

secs::Entity EntityFactory::makePlayer(float x, float y)
{
	secs::Entity player = m_world.processor().addEntity();

	auto& transform_comp = addComponent<TransformComponent>(player);
	transform_comp.position.set( x, y );

	addComponent<RenderComponent>(player);

	auto& animation_comp = addComponent<AnimationComponent>(player);
	animation_comp.animation = Assets::instance->phackmanWalk;

	addComponent<RenderFacingComponent>(player);
	addComponent<KeyboardInputComponent>(player);

	addComponent<MapAgentInputComponent>(player);
	addComponent<MapAgentStateComponent>(player);

    return player;
}
