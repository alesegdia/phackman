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

    auto& hcc = addComponent<HadronCollisionComponent>(player);
    hcc.body = new hadron::collision::Body(x, y, 12, 12);
    hcc.offset.set(10, 10);

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

    addComponent<EnemyComponent>(enemy);

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

    auto& cc = addComponent<CellComponent>(node);
    cc.type = CellType::IndustryCell;

    auto& hcc = addComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::collision::Body(x, y, 8, 8);
    hcc.offset.set(4,4);

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

    auto& cc = addComponent<CellComponent>(node);
    cc.type = CellType::IndustryCell;

    auto& hcc = addComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::collision::Body(x, y, 8, 8);
    hcc.offset.set(4,4);

    return node;
}

secs::Entity EntityFactory::makeBullet( float x, float y, Animation::SharedPtr anim, Facing direction, float speed )
{
    secs::Entity bullet = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(bullet);
    transform_comp.position.set( x, y );

    auto& rc = addComponent<RenderComponent>(bullet);
    rc.bitmap = anim->getFrame(0);

    auto& rf = addComponent<RenderFacingComponent>(bullet);
    rf.facing = direction;

    auto& ainput = addComponent<AgentInputComponent>(bullet);
    ainput.speed = speed;
    ainput.inputRequested = true;
    ainput.requestedFacing = direction;

    addComponent<AgentMapStateComponent>(bullet);
    addComponent<DieOnStopComponent>(bullet);

    auto& animation_comp = addComponent<AnimationComponent>(bullet);
    animation_comp.animation = anim;

    return bullet;
}

secs::Entity EntityFactory::makeLSBullet(float x, float y, Facing direction)
{
    return makeBullet(x, y, Assets::instance->lsBullet, direction, 175);
}

secs::Entity EntityFactory::makeTurretBullet(float x, float y, Facing direction)
{
    return makeBullet(x, y, Assets::instance->turretBullet, direction, 250);
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
    aic.lower_speed = 0;
    aic.normal_speed = 0;
    aic.speed = 0;

    addComponent<TileComponent>(building);

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

    addComponent<MapAwarenessComponent>(e);
    addComponent<ShootAtSightComponent>(e);

    auto& sc = addComponent<ShootComponent>(e);
    sc.shoot = [this](const secs::Entity& ent) {
        TransformComponent tc = m_world.component<TransformComponent>(ent);
        RenderFacingComponent rf = m_world.component<RenderFacingComponent>(ent);
        ShootComponent scc = m_world.component<ShootComponent>(ent);
        this->makeTurretBullet(tc.position.x(), tc.position.y(), scc.facing);
    };

    sc.rate = 0.8;

}
