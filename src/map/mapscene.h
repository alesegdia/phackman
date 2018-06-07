#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include <alligator/util/math.h>

#include "../map/mapgen.h"
#include "../ai/pfmap.h"
#include "../ai/blackboard.h"
#include "../game/assets.h"

class MapScene
{
public:
    MapScene()
    {
        m_map = LayoutBuilder().generate(ShapeStorage().makeSample());

        m_infectionMap = scale_down(*m_map, 2);

        m_solidnessMap = scale_down(*m_map, 2);

        m_nodesMap = scale_down(*m_map, 2);

        m_nodesMap = convolute3x3(*m_nodesMap, place_collectible_nodes);
        m_nodesMap->debugPrint();

        m_infectionMap->debugPrint();

        for( int i = 0; i < m_infectionMap->cols(); i++ )
        {
            for( int j = 0; j < m_infectionMap->rows(); j++ )
            {
                if( m_infectionMap->get(i, j) == 0 )
                {
                    m_infectionMap->set(i, j, 0);
                }
            }
        }

        m_renderMap = convolute3x3(*m_map, draw_map_tiles_convolutor);

        m_navmap.reset(new NavigationMap(m_map));

        Blackboard::instance.navigationMap = m_navmap;

    }

    void infect(int x, int y)
    {
        m_infectionMap->set(x, y, 3);
    }

    void desinfect(int x, int y)
    {
        m_infectionMap->set(x, y, 0);
    }

    std::shared_ptr<NavigationMap> navmap()
    {
        return m_navmap;
    }

    Matrix2Di::SharedPtr nodesMap()
    {
        return m_nodesMap;
    }

    void render()
    {
        al_hold_bitmap_drawing(true);
        for( int r = 0; r < m_renderMap->rows(); r++ )
        {
            for( int c = 0; c < m_renderMap->cols(); c++ )
            {
                int x1, y1, x2, y2;
                x1 = c * 16; y1 = r * 16;
                x2 = (c+1) * 16; y2 = (r+1) * 16;

                int frame = m_renderMap->get(c, r);

                int ncx, ncy;
                ncx = c / 2;
                ncy = r / 2;

                if( m_infectionMap->get(ncx, ncy) == 3 )
                {
                    frame += 30;
                }

                if( m_infectionMap->get(ncx, ncy) == 4 )
                {
                    frame += 60;
                }

                ALLEGRO_BITMAP* bm = Assets::instance->maptilesSheet->getFrame(frame);
                al_draw_bitmap(bm, x1, y1, 0);
            }
        }
        al_hold_bitmap_drawing(false);

    }

    int getSolidness(int x, int y)
    {
        return m_solidnessMap->get(x, y);
    }

    bool isInfected(int x, int y)
    {
        return m_infectionMap->get(x, y);
    }

    void debugRender()
    {
        for( int r = 0; r < m_map->rows(); r++ )
        {
            for( int c = 0; c < m_map->cols(); c++ )
            {
                int x1, y1, x2, y2;
                x1 = c * 16; y1 = r * 16;
                x2 = (c+1) * 16; y2 = (r+1) * 16;

                if( m_map->get(c, r) == 1 )
                {
                    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
                }
                else
                {
                    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
                }
            }
        }

        for( PathNode::SharedPtr node : m_navmap->nodes() )
        {
            float cx, cy;
            cx = (node->x()+1) * 16;
            cy = (node->y()+1) * 16;

            for( PathNode::SharedPtr neighboor : node->neighboors() )
            {
                int ncx, ncy;
                ncx = (neighboor->x()+1) * 16;
                ncy = (neighboor->y()+1) * 16;

                al_draw_line(cx, cy, ncx, ncy, al_map_rgba(0, 255, 255, 2), 1);
            }

            al_draw_filled_circle(cx, cy, 3, al_map_rgb(255, 0, 0));
        }

        for( PathNode::SharedPtr node : m_navmap->nodes() )
        {
            float x, y;
            x = (node->x()+1) * 16;
            y = (node->y()+1) * 16;
            al_draw_ellipse( x, y, 4, 4, al_map_rgb(255, 255, 0), 1);
        }

    }


private:
    Matrix2Di::SharedPtr m_map;
    Matrix2Di::SharedPtr m_renderMap;
    Matrix2Di::SharedPtr m_infectionMap;
    std::shared_ptr<NavigationMap> m_navmap;

    Matrix2Di::SharedPtr m_nodesMap;

    Matrix2Di::SharedPtr m_solidnessMap;


};

