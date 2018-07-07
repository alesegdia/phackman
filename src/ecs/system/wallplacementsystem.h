#pragma once

#include <alligator/input/input.h>
#include <secs/secs.h>

#include <allegro5/allegro_primitives.h>

#include "../component/components.h"
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
        u = Input::IsKeyJustPressed(ALLEGRO_KEY_UP);
        d = Input::IsKeyJustPressed(ALLEGRO_KEY_DOWN);
        l = Input::IsKeyJustPressed(ALLEGRO_KEY_LEFT);
        r = Input::IsKeyJustPressed(ALLEGRO_KEY_RIGHT);


        if( u|l|d|r )
        {
            m_world.processor().removeComponent<WallPlacementComponent>(e);
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
                    m_factory.makeBuildingOnWall(m_playerTile.x(), m_playerTile.y(), 0, f);
                }
            }

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
        m_playerTile = Vec2i( int(tc.position.x()+16), int(tc.position.y() + 16) );
        m_playerPos = tc.position;
        m_playerTile /= 32;

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
        al_draw_filled_rectangle(x * 32, y * 32, (x+1) * 32, (y+1) * 32, al_map_rgb(255, 0, 0));
    }

    secs::Engine& m_world;
    MapScene& m_mapScene;
    EntityFactory& m_factory;

    Vec2i m_playerTile;
    Vec2f m_playerPos;
    int m_up, m_down, m_left, m_right;

};



