#pragma once

#include <aether/aether.h>

#include "../map/mapgen.h"
#include "../map/placementmap.h"
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

        m_placementMap.reset( m_solidnessMap->cols(), m_solidnessMap->rows() );

        printf("SOLIDITY MAP\n");
        m_solidnessMap->debugPrint();
        printf("===========\n");

        m_enemyVisibilityMap = scale_down(*m_map, 2);
        printf("enemy visibility map\n");
        m_enemyVisibilityMap->debugPrint();
        printf("===========\n");
        fflush(0);

        m_nodesMap = scale_down(*m_map, 2);
        m_nodesMap = convolute3x3(*m_nodesMap, place_collectible_nodes);
        m_nodesMap->debugPrint();

        m_infectionMap->debugPrint();

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

    void undoReinforce(int x, int y)
    {
        desinfect(x, y);
    }

    void reinforce(int x, int y)
    {
        m_infectionMap->set(x, y, 4);
    }

    std::shared_ptr<NavigationMap> navmap()
    {
        return m_navmap;
    }

    aether::math::Matrix2Di::SharedPtr nodesMap()
    {
        return m_nodesMap;
    }

    aether::math::Matrix2Di::SharedPtr enemyVisibilityMap()
    {
        return m_enemyVisibilityMap;
    }

    void render()
    {
        al_hold_bitmap_drawing(true);
        for( int r = 0; r < m_renderMap->rows(); r++ )
        {
            for( int c = 0; c < m_renderMap->cols(); c++ )
            {
                int x1, y1;
                x1 = c * 16; y1 = r * 16;

                int frame = m_renderMap->get(c, r);

                int ncx, ncy;
                ncx = c / 2;
                ncy = r / 2;

                if( isInfected(ncx, ncy) )
                {
                    frame += 30;
                }

                if( isReinforced(ncx, ncy) )
                {
                    frame += 60;
                }

                auto bm = Assets::instance->maptilesSheet->getFrame(frame);
                bm->draw(x1, y1);
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
        return m_infectionMap->get(x, y) == 3;
    }

    bool isReinforced(int x, int y)
    {
        return m_infectionMap->get(x, y) == 4;
    }

    void toggleReinforced(int x, int y)
    {
        if( false == isInfected(x, y) )
        {
            if( isReinforced(x, y) )
            {
                desinfect(x, y);
            }
            else
            {
                reinforce(x, y);
            }
        }
        if( isReinforced(x, y) && ! isInfected(x, y) )
        {

        }
    }

    aether::math::Vec2f renderMapSize()
    {
        return aether::math::Vec2f(m_renderMap->cols(), m_renderMap->rows());
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

    PlacementMap& placementMap()
    {
        return m_placementMap;
    }


private:
    aether::math::Matrix2Di::SharedPtr m_map;
    aether::math::Matrix2Di::SharedPtr m_renderMap;
    aether::math::Matrix2Di::SharedPtr m_infectionMap;
    std::shared_ptr<NavigationMap> m_navmap;
    PlacementMap m_placementMap;

    aether::math::Matrix2Di::SharedPtr m_nodesMap;
    aether::math::Matrix2Di::SharedPtr m_solidnessMap;
    aether::math::Matrix2Di::SharedPtr m_enemyVisibilityMap;

};

