#pragma once

#include "../component/components.h"

#include <secs/secs.h>

class MapAwarenessSystem : public secs::TypedEntitySystem<TileComponent, MapAwarenessComponent>
{
public:
    MapAwarenessSystem(Matrix2Di::SharedPtr sensing_matrix)
        : m_sensingMatrix(sensing_matrix)
    {

    }

    void process(double delta, const secs::Entity &e, TileComponent &tlc, MapAwarenessComponent& mac)
    {
        for( int i = 0; i < 4; i++ )
        {
            handleDirection( (Facing)i, tlc, mac );
        }
    }

private:

    static constexpr int TILE_SOLID = 1;
    static constexpr int TILE_ENEMY = 2;

    void handleDirection( Facing direction, TileComponent& tlc, MapAwarenessComponent& mac )
    {
        bool scan_result = scan(tlc.current, direction);
        mac.setDirectionSensor(0, direction, scan_result );
        if( scan_result )
        {
            int a = 3;
        }
    }

    bool scan(Vec2i pos, Facing direction)
    {
        int tile = 0;
        bool did_sense = false;
        while( tile != 1 && did_sense == false )
        {
            advance(pos, direction);
            tile = m_sensingMatrix->get( pos.x(), pos.y() );
            did_sense = tile == 2;
        }
        return did_sense;
    }

    void advance(Vec2i& pos, Facing direction)
    {
        switch( direction )
        {
        case Facing::Right: pos.x(pos.x() + 1); break;
        case Facing::Left: pos.x(pos.x() - 1); break;
        case Facing::Down: pos.y(pos.y() + 1); break;
        case Facing::Up: pos.y(pos.y() - 1); break;
        }
    }

    Matrix2Di::SharedPtr m_sensingMatrix;

};
