#include "entityfactory.h"

EntityFactory::EntityFactory(secs::Engine &world)
	: m_world(world)
{

}

secs::Entity EntityFactory::makePlayer(float x, float y, OnDeathActionComponent::Action action)
{
	secs::Entity player = m_world.processor().addEntity();

	auto& transform_comp = addComponent<TransformComponent>(player);
	transform_comp.position.set( x, y );

	addComponent<RenderComponent>(player);

	auto& animation_comp = addComponent<AnimationComponent>(player);
	animation_comp.animation = Assets::instance->phackmanWalk;

    auto& hc = addComponent<HealthComponent>(player);
    hc.maxHealth = 10;

    addComponent<TileComponent>(player);
    addComponent<RenderFacingComponent>(player);
    addComponent<PlayerInputComponent>(player);

    auto& aic = addComponent<AgentInputComponent>(player);
    aic.lower_speed = 0.00004f;
    aic.normal_speed = 0.00008f;
    aic.speed = 0.00008f;

    addComponent<AgentMapStateComponent>(player);
    auto& sc = addComponent<ShootComponent>(player);
    sc.shoot = [this](const secs::Entity& e) {
        TransformComponent tc = m_world.component<TransformComponent>(e);
        RenderFacingComponent rf = m_world.component<RenderFacingComponent>(e);
        this->makeLSBullet(tc.position.x(), tc.position.y(), rf.facing);
    };
    sc.rate = 0.1e6;

    auto& ac = addComponent<AnimatorComponent>(player);
	ac.attack_animation = Assets::instance->phackmanAttack;
	ac.stand_animation = Assets::instance->phackmanStand;
    ac.walk_animation = Assets::instance->phackmanWalk;
    ac.desinfect_walk_animation = Assets::instance->phackmanDesinfectWalk;
    ac.desinfect_stand_animation = Assets::instance->phackmanDesinfectStand;

    auto& hcc = addComponent<HadronCollisionComponent>(player);
    hcc.body = new hadron::Body(x, y, 12, 12);
    hcc.offset.set(10, 10);

    auto& rsc = addComponent<ResourceStorageComponent>(player);
    rsc.reinforceCells = 10;

    auto& odac = addComponent<OnDeathActionComponent>(player);
    odac.action = action;

	return player;
}


secs::Entity EntityFactory::makeEnemy(float x, float y)
{
    secs::Entity enemy = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(enemy);
    transform_comp.position.set( x, y );

    auto& rc = addComponent<RenderComponent>(enemy);
    rc.offset = 0;

    auto& animation_comp = addComponent<AnimationComponent>(enemy);
    animation_comp.animation = Assets::instance->slimeWalk;

    addComponent<RenderFacingComponent>(enemy);
    addComponent<TileComponent>(enemy);

    auto& aic = addComponent<AgentInputComponent>(enemy);
    aic.speed = 0.00001f;

    addComponent<EnemyComponent>(enemy);

    addComponent<AgentMapStateComponent>(enemy);
    addComponent<AIAgentRandomWanderComponent>(enemy);
    auto& ic = addComponent<InfectComponent>(enemy);
    ic.desinfectDuration = 1e6;

    auto& hcc = addComponent<HadronCollisionComponent>(enemy);
    hcc.body = new hadron::Body(x, y, 14, 14);
    hcc.offset.set(8,8);

    auto& hc = addComponent<HealthComponent>(enemy);
    hc.maxHealth = 5;

    return enemy;
}

secs::Entity EntityFactory::makeSpawner(float x, float y)
{
    secs::Entity spawner = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(spawner);
    transform_comp.position.set( x+2, y +2);

    addComponent<RenderComponent>(spawner);

    auto& animation_comp = addComponent<AnimationComponent>(spawner);
    animation_comp.animation = Assets::instance->spawnerStand;

    auto& spawn = addComponent<SpawnComponent>(spawner);
    spawn.maxNumEntities = 3;

    addComponent<AlwaysShootComponent>(spawner);
    addComponent<AgentInputComponent>(spawner);

    auto& sc = addComponent<ShootComponent>(spawner);
    sc.rate = 3e6;
    sc.shoot = [this, spawner](const secs::Entity& ent) {
        auto& tc = m_world.component<TransformComponent>(ent);
        auto& spawn = m_world.component<SpawnComponent>(ent);
        if( spawn.currentEntities < spawn.maxNumEntities )
        {
            auto enemy = this->makeEnemy( tc.position.x() - 2, tc.position.y() - 2 );
            spawn.currentEntities++;
            auto& death = addComponent<OnDeathActionComponent>(enemy);
            death.action = [this, spawner](const secs::Entity& entity) {
                auto& spawn = m_world.component<SpawnComponent>(spawner);
                spawn.currentEntities--;
            };
        }
    };

    return spawner;
}

secs::Entity EntityFactory::makeIndustryNode(float x, float y)
{
    secs::Entity node = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(node);
    transform_comp.position.set( x, y );

    auto& rc = addComponent<RenderComponent>(node);
    rc.bitmap = Assets::instance->industryNode->getFrame(0).texture;

    auto& cc = addComponent<CellComponent>(node);
    cc.type = CellType::IndustryCell;

    auto& hcc = addComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::Body(x, y, 8, 8);
    hcc.offset.set(4,4);

    return node;
}

secs::Entity EntityFactory::makePowerNode(float x, float y)
{
    secs::Entity node = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(node);
    transform_comp.position.set( x, y );
    auto& rc = addComponent<RenderComponent>(node);
    rc.bitmap = Assets::instance->powerNode->getFrame(0).texture;

    auto& cc = addComponent<CellComponent>(node);
    cc.type = CellType::PowerCell;

    auto& hcc = addComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::Body(x, y, 8, 8);
    hcc.offset.set(4,4);

    return node;
}

secs::Entity EntityFactory::makeCountdownText(float x, float y, const char *text)
{
    secs::Entity t = m_world.processor().addEntity();

    auto& transform = addComponent<TransformComponent>(t);
    auto& death = addComponent<DeathTimerComponent>(t);
    auto& textcomp = addComponent<TextComponent>(t);
    auto& fac = addComponent<FadeComponent>(t);
    auto& fc = addComponent<FloatingComponent>(t);
    auto& ctc = addComponent<ColorTintComponent>(t);
    ctc.color = aether::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f);
    fc.speed = 0.07f;
    fac.rate = 0.008f;
    transform.position.set(x + 16, y-20);
    death.ttl = 2e6;
    textcomp.text = text;

    return t;
}

secs::Entity EntityFactory::makeBullet( float x, float y, aether::graphics::Animation::SharedPtr anim, Facing direction, float speed )
{
    secs::Entity bullet = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(bullet);
    transform_comp.position.set( x, y );

    auto& rc = addComponent<RenderComponent>(bullet);
    rc.bitmap = anim->getFrame(0).texture;

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

    auto& hcc = addComponent<HadronCollisionComponent>(bullet);
    hcc.body = new hadron::Body(x, y, 16, 16);
    hcc.offset.set(8, 8);

    return bullet;
}

secs::Entity EntityFactory::makeLSBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->lsBullet, direction, 0.0002f);
    addComponent<PlayerBulletComponent>(b);
    return b;
}

secs::Entity EntityFactory::makeTurretBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->turretBullet, direction, 0.0003f);
    addComponent<PlayerBulletComponent>(b);
    return b;
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
    addComponent<WallAwarePlacedComponent>(building);

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
    sc.rate = 2e5;
    sc.shoot = [this](const secs::Entity& ent) {
        TransformComponent tc = m_world.component<TransformComponent>(ent);
        ShootComponent scc = m_world.component<ShootComponent>(ent);
        this->makeTurretBullet(tc.position.x(), tc.position.y(), scc.facing);
    };

    auto& pcc = addComponent<PowerConsumerComponent>(e);
    pcc.unpowered_asset = Assets::instance->buildingsSheet->getFrame(0, 1);


	return e;
}


secs::Entity EntityFactory::makeCrucible( float x, float y )
{
    secs::Entity crucible = m_world.processor().addEntity();

    auto& tc = addComponent<TransformComponent>(crucible);
    tc.position.set( x, y );

    auto& rc = addComponent<RenderComponent>(crucible);
    rc.bitmap = *Assets::instance->buildingsSheet->getFrame(1, 1);

    return crucible;
}

