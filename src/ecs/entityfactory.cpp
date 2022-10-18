#include "entityfactory.h"

EntityFactory::EntityFactory(secs::Engine &world)
	: m_world(world)
{

}

secs::Entity EntityFactory::makePlayer(float x, float y, OnDeathActionComponent::Action action)
{
	secs::Entity player = m_world.GetEntityProcessor().AddEntity();

	auto& transform_comp = AddComponent<TransformComponent>(player);
	transform_comp.position.Set( x, y );

	AddComponent<RenderComponent>(player);

	auto& animation_comp = AddComponent<AnimationComponent>(player);
	animation_comp.animation = Assets::instance->phackmanWalk;

    auto& hc = AddComponent<HealthComponent>(player);
    hc.maxHealth = 10;

    AddComponent<TileComponent>(player);
    AddComponent<RenderFacingComponent>(player);
    AddComponent<PlayerInputComponent>(player);

    auto& aic = AddComponent<AgentInputComponent>(player);
    aic.lower_speed = 0.00004f;
    aic.normal_speed = 0.00008f;
    aic.speed = 0.00008f;

    AddComponent<AgentMapStateComponent>(player);
    auto& sc = AddComponent<ShootComponent>(player);
    sc.shoot = [this](const secs::Entity& e) {
        TransformComponent tc = m_world.GetComponent<TransformComponent>(e);
        RenderFacingComponent rf = m_world.GetComponent<RenderFacingComponent>(e);
        this->makeLSBullet(tc.position.GetX(), tc.position.GetY(), rf.facing);
    };
    sc.rate = 0.1e6;

    auto& ac = AddComponent<AnimatorComponent>(player);
	ac.attack_animation = Assets::instance->phackmanAttack;
	ac.stand_animation = Assets::instance->phackmanStand;
    ac.walk_animation = Assets::instance->phackmanWalk;
    ac.desinfect_walk_animation = Assets::instance->phackmanDesinfectWalk;
    ac.desinfect_stand_animation = Assets::instance->phackmanDesinfectStand;

    auto& hcc = AddComponent<HadronCollisionComponent>(player);
    hcc.body = new hadron::Body(x, y, 12, 12);
    hcc.offset.Set(10, 10);

    auto& rsc = AddComponent<ResourceStorageComponent>(player);
    rsc.reinforceCells = 10;

    auto& odac = AddComponent<OnDeathActionComponent>(player);
    odac.action = action;

	return player;
}


secs::Entity EntityFactory::makeEnemy(float x, float y)
{
    secs::Entity enemy = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(enemy);
    transform_comp.position.Set( x, y );

    auto& rc = AddComponent<RenderComponent>(enemy);
    rc.offset = 0;

    auto& animation_comp = AddComponent<AnimationComponent>(enemy);
    animation_comp.animation = Assets::instance->slimeWalk;

    AddComponent<RenderFacingComponent>(enemy);
    AddComponent<TileComponent>(enemy);

    auto& aic = AddComponent<AgentInputComponent>(enemy);
    aic.speed = 0.00001f;

    AddComponent<EnemyComponent>(enemy);

    AddComponent<AgentMapStateComponent>(enemy);
    AddComponent<AIAgentRandomWanderComponent>(enemy);
    auto& ic = AddComponent<InfectComponent>(enemy);
    ic.desinfectDuration = 1e6;

    auto& hcc = AddComponent<HadronCollisionComponent>(enemy);
    hcc.body = new hadron::Body(x, y, 14, 14);
    hcc.offset.Set(8,8);

    auto& hc = AddComponent<HealthComponent>(enemy);
    hc.maxHealth = 5;

    return enemy;
}

secs::Entity EntityFactory::makeSpawner(float x, float y)
{
    secs::Entity spawner = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(spawner);
    transform_comp.position.Set( x+2, y +2);

    AddComponent<RenderComponent>(spawner);

    auto& animation_comp = AddComponent<AnimationComponent>(spawner);
    animation_comp.animation = Assets::instance->spawnerStand;

    auto& spawn = AddComponent<SpawnComponent>(spawner);
    spawn.maxNumEntities = 3;

    AddComponent<AlwaysShootComponent>(spawner);
    AddComponent<AgentInputComponent>(spawner);

    auto& sc = AddComponent<ShootComponent>(spawner);
    sc.rate = 3e6;
    sc.shoot = [this, spawner](const secs::Entity& ent) {
        auto& tc = m_world.GetComponent<TransformComponent>(ent);
        auto& spawn = m_world.GetComponent<SpawnComponent>(ent);
        if( spawn.currentEntities < spawn.maxNumEntities )
        {
            auto enemy = this->makeEnemy( tc.position.GetX() - 2, tc.position.GetY() - 2 );
            spawn.currentEntities++;
            auto& death = AddComponent<OnDeathActionComponent>(enemy);
            death.action = [this, spawner](const secs::Entity& entity) {
                auto& spawn = m_world.GetComponent<SpawnComponent>(spawner);
                spawn.currentEntities--;
            };
        }
    };

    return spawner;
}

secs::Entity EntityFactory::makeIndustryNode(float x, float y)
{
    secs::Entity node = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(node);
    transform_comp.position.Set( x, y );

    auto& rc = AddComponent<RenderComponent>(node);
    rc.bitmap = Assets::instance->industryNode->GetFrame(0).texture;

    auto& cc = AddComponent<CellComponent>(node);
    cc.type = CellType::IndustryCell;

    auto& hcc = AddComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::Body(x, y, 8, 8);
    hcc.offset.Set(4,4);

    return node;
}

secs::Entity EntityFactory::makePowerNode(float x, float y)
{
    secs::Entity node = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(node);
    transform_comp.position.Set( x, y );
    auto& rc = AddComponent<RenderComponent>(node);
    rc.bitmap = Assets::instance->powerNode->GetFrame(0).texture;

    auto& cc = AddComponent<CellComponent>(node);
    cc.type = CellType::PowerCell;

    auto& hcc = AddComponent<HadronCollisionComponent>(node);
    hcc.body = new hadron::Body(x, y, 8, 8);
    hcc.offset.Set(4,4);

    return node;
}

secs::Entity EntityFactory::makeCountdownText(float x, float y, const char *text)
{
    secs::Entity t = m_world.GetEntityProcessor().AddEntity();

    auto& transform = AddComponent<TransformComponent>(t);
    auto& death = AddComponent<DeathTimerComponent>(t);
    auto& textcomp = AddComponent<TextComponent>(t);
    auto& fac = AddComponent<FadeComponent>(t);
    auto& fc = AddComponent<FloatingComponent>(t);
    auto& ctc = AddComponent<ColorTintComponent>(t);
    ctc.color = aether::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f);
    fc.speed = 0.07f;
    fac.rate = 0.008f;
    transform.position.Set(x + 16, y-20);
    death.ttl = 2e6;
    textcomp.text = text;

    return t;
}

secs::Entity EntityFactory::makeBullet( float x, float y, aether::graphics::Animation::SharedPtr anim, Facing direction, float speed )
{
    secs::Entity bullet = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(bullet);
    transform_comp.position.Set( x, y );

    auto& rc = AddComponent<RenderComponent>(bullet);
    rc.bitmap = anim->GetFrame(0).texture;

    auto& rf = AddComponent<RenderFacingComponent>(bullet);
    rf.facing = direction;

    auto& ainput = AddComponent<AgentInputComponent>(bullet);
    ainput.speed = speed;
    ainput.inputRequested = true;
    ainput.requestedFacing = direction;

    AddComponent<AgentMapStateComponent>(bullet);
    AddComponent<DieOnStopComponent>(bullet);

    auto& animation_comp = AddComponent<AnimationComponent>(bullet);
    animation_comp.animation = anim;

    auto& hcc = AddComponent<HadronCollisionComponent>(bullet);
    hcc.body = new hadron::Body(x, y, 16, 16);
    hcc.offset.Set(8, 8);

    return bullet;
}

secs::Entity EntityFactory::makeLSBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->lsBullet, direction, 0.0002f);
    AddComponent<PlayerBulletComponent>(b);
    return b;
}

secs::Entity EntityFactory::makeTurretBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->turretBullet, direction, 0.0003f);
    AddComponent<PlayerBulletComponent>(b);
    return b;
}

secs::Entity EntityFactory::makeBuildingOnWall(int tile_x, int tile_y, int building_type, Facing facing)
{
    float x = tile_x * 32;
    float y = tile_y * 32;

    secs::Entity building = m_world.GetEntityProcessor().AddEntity();

    auto& tc = AddComponent<TransformComponent>(building);
    tc.position.SetX(x);
    tc.position.SetY(y);

    AddComponent<RenderComponent>(building);

    auto& rfc = AddComponent<RenderFacingComponent>(building);
    rfc.facing = facing;

    auto& aic = AddComponent<AgentInputComponent>(building);
    aic.lower_speed = 0;
    aic.normal_speed = 0;
    aic.speed = 0;

    AddComponent<TileComponent>(building);
    AddComponent<WallAwarePlacedComponent>(building);

    switch( building_type )
    {
    case 0: /* TURRET */
        makeBuildingTurret(building);
    }

    return building;
}

secs::Entity EntityFactory::makeBuildingTurret( const secs::Entity& e )
{
    auto& animator = AddComponent<AnimatorComponent>(e);
    animator.stand_animation = Assets::instance->turretStand;

    auto& ac = AddComponent<AnimationComponent>(e);
    ac.animation = Assets::instance->turretStand;

    AddComponent<MapAwarenessComponent>(e);
    AddComponent<ShootAtSightComponent>(e);

    auto& sc = AddComponent<ShootComponent>(e);
    sc.rate = 2e5;
    sc.shoot = [this](const secs::Entity& ent) {
        TransformComponent tc = m_world.GetComponent<TransformComponent>(ent);
        ShootComponent scc = m_world.GetComponent<ShootComponent>(ent);
        this->makeTurretBullet(tc.position.GetX(), tc.position.GetY(), scc.facing);
    };

    auto& pcc = AddComponent<PowerConsumerComponent>(e);
    pcc.unpowered_asset = Assets::instance->buildingsSheet->GetFrame(0, 1);


	return e;
}


secs::Entity EntityFactory::makeCrucible( float x, float y )
{
    secs::Entity crucible = m_world.GetEntityProcessor().AddEntity();

    auto& tc = AddComponent<TransformComponent>(crucible);
    tc.position.Set( x, y );

    auto& rc = AddComponent<RenderComponent>(crucible);
    rc.bitmap = *Assets::instance->buildingsSheet->GetFrame(1, 1);

    return crucible;
}

