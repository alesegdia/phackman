#pragma once

/*
#include <allegro5/allegro5.h>
#include <alligator/util/matrix.h>

class MapSolidDebug
{

    typedef Matrix2D<int> Map;
    typedef std::shared_ptr<Map> MapPtr;

public:
    MapSolidDebug( MapPtr map )
        : m_map(map)
    {

    }

    void Render()
    {
        // HACER NODOS EN CENTRO CUADRICULA Y VER COMO QUEDAN :)
        ALLEGRO_COLOR color;
        for( int i = 0; i < m_map->GetColsNumber(); i++ )
        {
            for( int j = 0; j < m_map->GetRowsNumber(); j++ )
            {
                int tile = m_map->GetCell(i, j);
                if( tile == 1 ) {
                    color = al_map_rgba(255, 0, 0, 128);
                } else {
                    color = al_map_rgba(0, 0, 255, 128);
                }

                static constexpr int SCALE = 1;
                static constexpr int SIZE = 16;
                float x1, y1, x2, y2;
                x1 = SCALE * SIZE * i;
                y1 = SCALE * SIZE  * j;
                x2 = x1 + SIZE * SCALE;
                y2 = y1 + SIZE * SCALE;
                al_draw_rectangle(x1, y1, x2-1, y2-1, color, 1);
            }
        }

    }

private:
    MapPtr m_map;

};

*/