#include "entityfactory.h"

#include "aether/math/tween.h"
#include "../constants.h"

EntityFactory::EntityFactory(secs::Engine &world)
	: m_world(world)
{

}

secs::Entity EntityFactory::makePlayer(float x, float y, OnDeathActionComponent::Action action)
{
	secs::Entity player = m_world.GetEntityProcessor().AddEntity();
    m_playerEntity = player;

	auto& transform_comp = AddComponent<TransformComponent>(player);
	transform_comp.position.Set( x, y );

	AddComponent<RenderComponent>(player);

	auto& animation_comp = AddComponent<AnimationComponent>(player);
	animation_comp.animation = Assets::instance->assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("anim-phackman.json")->anims["PhackWalk"];

    auto& hc = AddComponent<HealthComponent>(player);
    hc.maxHealth = 10;

    AddComponent<TileComponent>(player);
    AddComponent<RenderFacingComponent>(player);
    AddComponent<PlayerInputComponent>(player);

    auto& aic = AddComponent<AgentInputComponent>(player);
	aic.lowest_speed = Constants::Player::LowestSpeed;
	aic.low_speed = Constants::Player::LowSpeed;
	aic.normal_speed = Constants::Player::NormalSpeed;
	aic.fast_speed = Constants::Player::FastSpeed;
    aic.normallow_speed = Constants::Player::NormalLowSpeed;
    aic.speed = Constants::Player::Speed;

    AddComponent<AgentMapStateComponent>(player);
    auto& sc = AddComponent<ShootComponent>(player);
    sc.shoot = [this](const secs::Entity& e) {
        TransformComponent tc = m_world.GetComponent<TransformComponent>(e);
        RenderFacingComponent rf = m_world.GetComponent<RenderFacingComponent>(e);
        this->makeLSBullet(tc.position.GetX(), tc.position.GetY(), rf.facing);
    };
    sc.rate = Constants::GunSkill::Rate;

    auto phackmanAnims = Assets::instance->assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("anim-phackman.json")->anims;
    auto& ac = AddComponent<AnimatorComponent>(player);
	ac.attack_animation = phackmanAnims["PhackShoot"];
	ac.stand_animation = phackmanAnims["PhackStand"];
    ac.walk_animation = phackmanAnims["PhackWalk"];
    ac.desinfect_walk_animation = phackmanAnims["PhackWalkInfect"];
	ac.desinfect_stand_animation = phackmanAnims["PhackStandInfect"];
	ac.carry_crucible_walk_animation = phackmanAnims["PhackCarryWalk"];
	ac.carry_crucible_stand_animation = phackmanAnims["PhackCarryStand"];

    auto& hcc = AddComponent<HadronCollisionComponent>(player);
    hcc.body = new hadron::Body(x, y, 12, 12);
    hcc.offset.Set(10, 10);

    auto& rsc = AddComponent<ResourceStorageComponent>(player);
    rsc.reinforceCells = 10;

    auto& odac = AddComponent<OnDeathActionComponent>(player);
    odac.action = action;

	return player;
}


secs::Entity EntityFactory::makeEnemy(float x, float y, int level)
{
    secs::Entity enemy = m_world.GetEntityProcessor().AddEntity();

    auto& transform_comp = AddComponent<TransformComponent>(enemy);
    transform_comp.position.Set( x, y );

    auto& rc = AddComponent<RenderComponent>(enemy);
    rc.offset = 0;

    auto& animation_comp = AddComponent<AnimationComponent>(enemy);
    animation_comp.animation = Assets::instance->assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("anim-phackman.json")->anims["SlimeWalk"];

    AddComponent<RenderFacingComponent>(enemy);
    AddComponent<TileComponent>(enemy);

    auto& aic = AddComponent<AgentInputComponent>(enemy);
    aic.speed = 0.00002f + 0.00001f * level + ((rand()%100) / 100.f) * 0.000005f;

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

	auto& hcc = AddComponent<HadronCollisionComponent>(spawner);
	hcc.body = new hadron::Body(x, y, 14, 14);
	hcc.offset.Set(8, 8);

	AddComponent<EnemyComponent>(spawner);

    auto& sc = AddComponent<ShootComponent>(spawner);
    sc.rate = 3e6;
    sc.shoot = [this, spawner](const secs::Entity& ent) {
        auto& tc = m_world.GetComponent<TransformComponent>(ent);
        auto& spawn = m_world.GetComponent<SpawnComponent>(ent);
        if( spawn.currentEntities < spawn.maxNumEntities )
        {
            auto& plic = m_world.GetComponent<AgentInputComponent>(m_playerEntity);
            auto enemyLevel = plic.carryCrucible ? 2 : 0;
            auto enemy = this->makeEnemy( tc.position.GetX() - 2, tc.position.GetY() - 2, enemyLevel );
            spawn.currentEntities++;
            auto& death = AddComponent<OnDeathActionComponent>(enemy);
            death.action = [this, spawner](const secs::Entity& entity) {
                auto& spawn = m_world.GetComponent<SpawnComponent>(spawner);
                spawn.currentEntities--;
            };
        }
    };

    m_world.GetEntityProcessor().TagEntity(spawner, "spawner");

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

secs::Entity EntityFactory::MakeCountdownText(float x, float y, const char *text, aether::graphics::Color c)
{
    secs::Entity t = m_world.GetEntityProcessor().AddEntity();

    auto& transform = AddComponent<TransformComponent>(t);
    auto& death = AddComponent<DeathTimerComponent>(t);
    auto& textcomp = AddComponent<TextComponent>(t);
    auto& fac = AddComponent<FadeComponent>(t);
    auto& fc = AddComponent<FloatingComponent>(t);
    auto& ctc = AddComponent<ColorTintComponent>(t);
    ctc.color = c;
    fc.speed = 0.03f;
    fac.rate = 0.012f;
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
    auto& odac = AddComponent<OnDeathActionComponent>(bullet);
    odac.action = [=](const secs::Entity& e) {
        auto& tc = m_world.GetEntityProcessor().GetComponent<TransformComponent>(bullet);
        MakeExplosions(tc.position.GetX(), tc.position.GetY());
    };

    auto& animation_comp = AddComponent<AnimationComponent>(bullet);
    animation_comp.animation = anim;

    auto& hcc = AddComponent<HadronCollisionComponent>(bullet);
    hcc.body = new hadron::Body(x, y, 16, 16);
    hcc.offset.Set(8, 8);

    return bullet;
}

secs::Entity EntityFactory::makeLSBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("anim-phackman.json")->anims["PhackBullet"], direction, 0.0002f);
    AddComponent<BulletComponent>(b);
    return b;
}

secs::Entity EntityFactory::MakeTurretBullet(float x, float y, Facing direction)
{
    secs::Entity b = makeBullet(x, y, Assets::instance->turretBullet, direction, 0.0003f);
    AddComponent<BulletComponent>(b);
    return b;
}

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2

secs::Entity EntityFactory::MakeExplosion(float x, float y)
{
    secs::Entity e = m_world.GetEntityProcessor().AddEntity();
    auto& tc = AddComponent<TransformComponent>(e);
    static constexpr int RANDOM_OFFSET = 8;
    tc.position.SetX(x + rand() % RANDOM_OFFSET - RANDOM_OFFSET/2);
    tc.position.SetY(y + rand() % RANDOM_OFFSET - RANDOM_OFFSET/2);
    tc.angle = M_PI_2 * (rand() % 4);
    AddComponent<RenderComponent>(e);
    auto& animation_comp = AddComponent<AnimationComponent>(e);
    auto& anim = Assets::instance->assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("explosion.json")->anims["explosion"];
    anim->SetWrapMode(aether::graphics::Animation::WrapMode::Once);
    animation_comp.animation = anim;
    animation_comp.animationData.onAnimationFinished = [=]() {
        m_world.GetEntityProcessor().RemoveEntity(e);
    };
    return e;
}

void EntityFactory::MakeExplosions(float x, float y)
{
    for (int i = 0; i < 3; i++)
    {
        aether::TimerManager::GetInstance().CreateTimer(uint64_t(5e4 * i)).OnExpire([=]() { MakeExplosion(x, y); });
    }
}

secs::Entity EntityFactory::MakeBuildingOnWall(int tile_x, int tile_y, int building_type, Facing facing)
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
    aic.low_speed = 0;
    aic.normal_speed = 0;
    aic.speed = 0;

    AddComponent<TileComponent>(building);
    AddComponent<WallAwarePlacedComponent>(building);

    switch( building_type )
    {
    case 0: /* TURRET */
        MakeBuildingTurret(building);
    }

    return building;
}

secs::Entity EntityFactory::MakeBuildingTurret( const secs::Entity& e )
{
    auto& ac = AddComponent<AnimationComponent>(e);
    ac.animation = Assets::instance->turretStand;

    AddComponent<MapAwarenessComponent>(e);
    AddComponent<ShootAtSightComponent>(e);

    auto& sc = AddComponent<ShootComponent>(e);
    sc.rate = 2e5;
    sc.shoot = [this](const secs::Entity& ent) {
        TransformComponent tc = m_world.GetComponent<TransformComponent>(ent);
        ShootComponent scc = m_world.GetComponent<ShootComponent>(ent);
        this->MakeTurretBullet(tc.position.GetX(), tc.position.GetY(), scc.facing);
    };

    auto& pcc = AddComponent<PowerConsumerComponent>(e);
    pcc.unpowered_asset = Assets::instance->buildingsSheet->GetFrame(0, 1);


	return e;
}


secs::Entity EntityFactory::MakeCrucible( float x, float y )
{
    secs::Entity crucible = m_world.GetEntityProcessor().AddEntity();

    auto& tc = AddComponent<TransformComponent>(crucible);
    tc.position.Set( x, y );

    AddComponent<TileComponent>(crucible);


    auto& rc = AddComponent<RenderComponent>(crucible);
    rc.bitmap = *Assets::instance->buildingsSheet->GetFrame(1, 1);


    return crucible;
}


secs::Entity EntityFactory::MakeDoor(float x, float y)
{
	secs::Entity entity = m_world.GetEntityProcessor().AddEntity();

	auto& tc = AddComponent<TransformComponent>(entity);
	tc.position.Set(x, y);

	AddComponent<TileComponent>(entity);

	auto& rc = AddComponent<RenderComponent>(entity);
	rc.bitmap = *Assets::instance->buildingsSheet->GetFrame(3, 0);
	AddComponent<CrucibleComponent>(entity);

	auto& hcc = AddComponent<HadronCollisionComponent>(entity);
	hcc.body = new hadron::Body(x, y, 32, 32);
	hcc.offset.Set(0, 0);

	return entity;
}