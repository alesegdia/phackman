#pragma once

#include <secs/secs.h>

#include "../components.h"
#include "systemgroups.h"

#include "../../map/mapscene.h"

#include "../entityfactory.h"

class WallPlacementSystem : public secs::TypedEntitySystem<WallPlacementComponent, TransformComponent>
{
public:

    WallPlacementSystem( secs::Engine& world, MapScene& map_scene, EntityFactory& f )
        : m_world(world),
          m_mapScene(map_scene),
          m_factory(f)
    {
        SetStepConfiguration(true, true);
        SetExecutionPriority(10);
    }

    void process(double delta, const secs::Entity &e, WallPlacementComponent &wpc, TransformComponent& tc) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(wpc);
        SECS_UNUSED(tc);

        bool u, d, l, r;
        u = aether::core::is_key_just_pressed(aether::core::KeyCode::Up);
        d = aether::core::is_key_just_pressed(aether::core::KeyCode::Down);
        l = aether::core::is_key_just_pressed(aether::core::KeyCode::Left);
        r = aether::core::is_key_just_pressed(aether::core::KeyCode::Right);


        if( u|l|d|r )
        {
            Facing f;
            if( u ) f = Facing::Down;
            if( d ) f = Facing::Up;
            if( l ) f = Facing::Right;
            if( r ) f = Facing::Left;
            if( (u && m_up) ||
                (d && m_down) ||
                (l && m_left) ||
                (r && m_right) )
            {
                if( true == m_mapScene.IsReinforced(m_playerTile.GetX(), m_playerTile.GetY()) )
                {
                    if( true == m_mapScene.placementMap().isUsed( m_playerTile.GetX(), m_playerTile.GetY(), f ) )
                    {
                        m_factory.MakeCountdownText( tc.position.GetX(), tc.position.GetY(), "no space", aether::graphics::Color::Red);
                    }
                    else
                    {
                        auto& rsc = GetComponent<ResourceStorageComponent>(e);
                        static constexpr int COST = 3;
                        if( rsc.industryCells >= COST )
                        {
                            rsc.industryCells -= COST;
                            m_factory.MakeBuildingOnWall(m_playerTile.GetX(), m_playerTile.GetY(), 0, f);
                            m_factory.MakeCountdownText( tc.position.GetX(), tc.position.GetY(), "turret built", aether::graphics::Color::Cyan);
                        }
                        else
                        {
                            m_factory.MakeCountdownText( tc.position.GetX(), tc.position.GetY(), "not enough nodes", aether::graphics::Color::Red);
                        }
                    }
                }
            }
            GetEntityProcessor()->RemoveComponent<WallPlacementComponent>(e);
        }
    }


    void Render(const secs::Entity &e) override
    {
        SECS_UNUSED(e);
        if( m_up == 1 ) debugDrawRect(m_playerTile.GetX(), m_playerTile.GetY() - 1);
        if( m_down == 1 ) debugDrawRect(m_playerTile.GetX(), m_playerTile.GetY() + 1);
        if( m_right == 1 ) debugDrawRect(m_playerTile.GetX() + 1, m_playerTile.GetY());
        if( m_left == 1 ) debugDrawRect(m_playerTile.GetX() - 1, m_playerTile.GetY());
    }

    void OnEntityAdded(const secs::Entity &e) override
    {
        m_world.DisableGroup( SystemGroups::GuiStop );
        auto& tc = GetComponent<TransformComponent>(e);
        auto& aic = GetComponent<AgentInputComponent>(e);
        aic.inputRequested = false;
        computePossiblePlaceWalls(tc);
    }

    void OnEntityRemoved(const secs::Entity &e) override
    {
        SECS_UNUSED(e);
        m_world.EnableGroup( SystemGroups::GuiStop );
    }

private:

    void computePossiblePlaceWalls(TransformComponent& tc)
    {
        m_playerTile = aether::math::Vec2i( int(tc.position.GetX()+16), int(tc.position.GetY() + 16) );
        m_playerPos = tc.position;
        m_playerTile = m_playerTile / 32;

        printf("TILE: %d, %d\n", m_playerTile.GetX(), m_playerTile.GetY()); fflush(0);
        printf("POS: %f, %f\n", m_playerPos.GetX(), m_playerPos.GetY()); fflush(0);

        m_up = m_mapScene.GetSolidness( m_playerTile.GetX(), m_playerTile.GetY() - 1 );
        m_down = m_mapScene.GetSolidness( m_playerTile.GetX(), m_playerTile.GetY() + 1 );
        m_left = m_mapScene.GetSolidness( m_playerTile.GetX() - 1, m_playerTile.GetY() );
        m_right = m_mapScene.GetSolidness( m_playerTile.GetX() + 1, m_playerTile.GetY() );
        //printf("u: %d, d: %d, l: %d, r: %d\n", u, d, l, r); fflush(0);
    }

    void debugDrawRect(int x, int y)
    {
        aether::graphics::draw_filled_rectangle(x * 32, y * 32, 32, 32, aether::graphics::Color(1.0f, 0.0f, 0.0f));
    }

    secs::Engine& m_world;
    MapScene& m_mapScene;
    EntityFactory& m_factory;

    aether::math::Vec2i m_playerTile;
    aether::math::Vec2f m_playerPos;
    int m_up, m_down, m_left, m_right;

};



