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
        setStepConfiguration(true, true);
        setExecutionPriority(10);
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
                if( true == m_mapScene.isReinforced(m_playerTile.x(), m_playerTile.y()) )
                {
                    if( true == m_mapScene.placementMap().isUsed( m_playerTile.x(), m_playerTile.y(), f ) )
                    {
                        m_factory.makeCountdownText( tc.position.x(), tc.position.y(), "no space" );
                    }
                    else
                    {
                        auto& rsc = component<ResourceStorageComponent>(e);
                        static constexpr int COST = 3;
                        if( rsc.industryCells >= COST )
                        {
                            rsc.industryCells -= COST;
                            m_factory.makeBuildingOnWall(m_playerTile.x(), m_playerTile.y(), 0, f);
                            m_factory.makeCountdownText( tc.position.x(), tc.position.y(), "turret built" );
                        }
                        else
                        {
                            m_factory.makeCountdownText( tc.position.x(), tc.position.y(), "not enough nodes" );
                        }
                    }
                }
            }
            processor()->removeComponent<WallPlacementComponent>(e);
        }
    }


    void render(const secs::Entity &e) override
    {
        SECS_UNUSED(e);
        if( m_up == 1 ) debugDrawRect(m_playerTile.x(), m_playerTile.y() - 1);
        if( m_down == 1 ) debugDrawRect(m_playerTile.x(), m_playerTile.y() + 1);
        if( m_right == 1 ) debugDrawRect(m_playerTile.x() + 1, m_playerTile.y());
        if( m_left == 1 ) debugDrawRect(m_playerTile.x() - 1, m_playerTile.y());
    }

    void onAdded(const secs::Entity &e) override
    {
        m_world.disableGroup( SystemGroups::GuiStop );
        auto& tc = component<TransformComponent>(e);
        auto& aic = component<AgentInputComponent>(e);
        aic.inputRequested = false;
        computePossiblePlaceWalls(tc);
    }

    void onRemoved(const secs::Entity &e) override
    {
        SECS_UNUSED(e);
        m_world.enableGroup( SystemGroups::GuiStop );
    }

private:

    void computePossiblePlaceWalls(TransformComponent& tc)
    {
        m_playerTile = aether::math::Vec2i( int(tc.position.x()+16), int(tc.position.y() + 16) );
        m_playerPos = tc.position;
        m_playerTile = m_playerTile / 32;

        printf("TILE: %d, %d\n", m_playerTile.x(), m_playerTile.y()); fflush(0);
        printf("POS: %f, %f\n", m_playerPos.x(), m_playerPos.y()); fflush(0);

        m_up = m_mapScene.getSolidness( m_playerTile.x(), m_playerTile.y() - 1 );
        m_down = m_mapScene.getSolidness( m_playerTile.x(), m_playerTile.y() + 1 );
        m_left = m_mapScene.getSolidness( m_playerTile.x() - 1, m_playerTile.y() );
        m_right = m_mapScene.getSolidness( m_playerTile.x() + 1, m_playerTile.y() );
        //printf("u: %d, d: %d, l: %d, r: %d\n", u, d, l, r); fflush(0);
    }

    void debugDrawRect(int x, int y)
    {
        aether::graphics::draw_filled_rectangle(x * 32, y * 32, (x+1) * 32, (y+1) * 32, aether::graphics::Color(1.0f, 0.0f, 0.0f));
    }

    secs::Engine& m_world;
    MapScene& m_mapScene;
    EntityFactory& m_factory;

    aether::math::Vec2i m_playerTile;
    aether::math::Vec2f m_playerPos;
    int m_up, m_down, m_left, m_right;

};



