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

	addComponent<AgentInputComponent>(player);
	addComponent<AgentMapStateComponent>(player);

	AnimatorComponent& ac = addComponent<AnimatorComponent>(player);
	ac.attack_animation = Assets::instance->phackmanAttack;
	ac.stand_animation = Assets::instance->phackmanStand;
	ac.walk_animation = Assets::instance->phackmanWalk;

	return player;
}


secs::Entity EntityFactory::makeEnemy(float x, float y)
{
	secs::Entity enemy = m_world.processor().addEntity();

	auto& transform_comp = addComponent<TransformComponent>(enemy);
	transform_comp.position.set( x, y );

	addComponent<RenderComponent>(enemy);

	auto& animation_comp = addComponent<AnimationComponent>(enemy);
	animation_comp.animation = Assets::instance->phackmanWalk;

	addComponent<RenderFacingComponent>(enemy);
	addComponent<KeyboardInputComponent>(enemy);

	addComponent<AgentInputComponent>(enemy);
	addComponent<AgentMapStateComponent>(enemy);

	return enemy;
}
