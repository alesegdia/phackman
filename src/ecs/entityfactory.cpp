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

    addComponent<TileComponent>(player);
    addComponent<RenderFacingComponent>(player);
    addComponent<KeyboardInputComponent>(player);

	addComponent<AgentInputComponent>(player);
    addComponent<AgentMapStateComponent>(player);
    auto& sc = addComponent<ShootComponent>(player);
    sc.shoot = [this](const secs::Entity& e) {
        TransformComponent tc = m_world.component<TransformComponent>(e);
        RenderFacingComponent rf = m_world.component<RenderFacingComponent>(e);
        auto b = this->makeLSBullet(tc.position.x(), tc.position.y(), rf.facing);
        auto& ams = m_world.component<AgentMapStateComponent>(e);
        auto& amsb = m_world.component<AgentMapStateComponent>(b);
        amsb.lastNode = ams.lastNode;
        amsb.targetNode = ams.targetNode;
    };
    sc.rate = 0.2;

	AnimatorComponent& ac = addComponent<AnimatorComponent>(player);
	ac.attack_animation = Assets::instance->phackmanAttack;
	ac.stand_animation = Assets::instance->phackmanStand;
    ac.walk_animation = Assets::instance->phackmanWalk;
    ac.desinfect_walk_animation = Assets::instance->phackmanDesinfectWalk;
    ac.desinfect_stand_animation = Assets::instance->phackmanDesinfectStand;

	return player;
}


secs::Entity EntityFactory::makeEnemy(float x, float y)
{
    secs::Entity enemy = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(enemy);
    transform_comp.position.set( x, y );

    addComponent<RenderComponent>(enemy);

    auto& animation_comp = addComponent<AnimationComponent>(enemy);
    animation_comp.animation = Assets::instance->slimeWalk;

    addComponent<RenderFacingComponent>(enemy);
    addComponent<TileComponent>(enemy);

    auto& ainput = addComponent<AgentInputComponent>(enemy);
    ainput.speed = 20;

    addComponent<AgentMapStateComponent>(enemy);
    addComponent<AIAgentRandomWanderComponent>(enemy);
    auto& ic = addComponent<InfectComponent>(enemy);
    ic.desinfectDuration = 0.8f;

    return enemy;
}

secs::Entity EntityFactory::makeSpawner(float x, float y)
{
    secs::Entity enemy = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(enemy);
    transform_comp.position.set( x+2, y +2);

    addComponent<RenderComponent>(enemy);

    auto& animation_comp = addComponent<AnimationComponent>(enemy);
    animation_comp.animation = Assets::instance->spawnerStand;

    return enemy;
}

secs::Entity EntityFactory::makeIndustryNode(float x, float y)
{
    secs::Entity node = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(node);
    transform_comp.position.set( x, y );
    addComponent<RenderComponent>(node);
    auto& animation_comp = addComponent<AnimationComponent>(node);
    animation_comp.animation = Assets::instance->industryNode;

    return node;
}

secs::Entity EntityFactory::makePowerNode(float x, float y)
{
    secs::Entity node = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(node);
    transform_comp.position.set( x, y );
    addComponent<RenderComponent>(node);
    auto& animation_comp = addComponent<AnimationComponent>(node);
    animation_comp.animation = Assets::instance->powerNode;

    return node;
}

secs::Entity EntityFactory::makeLSBullet(float x, float y, Facing direction)
{
    secs::Entity bullet = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(bullet);
    transform_comp.position.set( x, y );

    addComponent<RenderComponent>(bullet);

    auto& animation_comp = addComponent<AnimationComponent>(bullet);
    animation_comp.animation = Assets::instance->lsBullet;

    auto& rf = addComponent<RenderFacingComponent>(bullet);
    rf.facing = direction;

    auto& ainput = addComponent<AgentInputComponent>(bullet);
    ainput.speed = 200;
    ainput.inputRequested = true;
    ainput.requestedFacing = direction;

    addComponent<AgentMapStateComponent>(bullet);

    addComponent<DieOnStopComponent>(bullet);

    return bullet;
}

secs::Entity EntityFactory::makeBuildingOnWall(int tile_x, int tile_y, int building_type, Facing facing)
{
    float x = tile_x * 32;
    float y = tile_y * 32;

    secs::Entity building = m_world.processor().addEntity();

    auto& tc = addComponent<TransformComponent>(building);
    tc.position.x(x);
    tc.position.y(y);

    addComponent<RenderComponent>(building);

    auto& rfc = addComponent<RenderFacingComponent>(building);
    rfc.facing = facing;

    auto& aic = addComponent<AgentInputComponent>(building);

    switch( building_type )
    {
    case 0: /* TURRET */
        makeBuildingTurret(building);
    }

    return building;
}

secs::Entity EntityFactory::makeBuildingTurret( const secs::Entity& e )
{
    auto& animator = addComponent<AnimatorComponent>(e);
    animator.stand_animation = Assets::instance->turretStand;

    auto& ac = addComponent<AnimationComponent>(e);
    ac.animation = Assets::instance->turretStand;
}
