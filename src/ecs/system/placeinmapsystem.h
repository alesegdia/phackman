#pragma once

#include <secs/secs.h>
#include <aether/aether.h>
#include "../components.h"
#include "../../map/mapscene.h"


class PlaceInMapSystem : public secs::TypedEntitySystem<TileComponent>
{
public:

    PlaceInMapSystem( aether::math::Matrix2Di::SharedPtr output_matrix, int brush )
        : m_outputMatrix(output_matrix),
          m_brush(brush)
    {

    }

    void process( double delta, const secs::Entity &e, TileComponent& tlc ) override
    {
        SECS_UNUSED(e);
        SECS_UNUSED(delta);
        // this can lead to an enemy placing a 0 where a previous enemy is present and has placed a 1
        // we will just keep this in mind if this is an issue in the future, which I think will not
        // an option is to clean all the map at the preProcess()
        if( tlc.current != tlc.previous )
        {
            m_outputMatrix->set(tlc.previous.x(), tlc.previous.y(), 0);
            m_outputMatrix->set(tlc.current.x(), tlc.current.y(), m_brush);
        }
    }

    void postUpdate(double delta) override
    {
        SECS_UNUSED(delta);
        // m_outputMatrix->debugPrint();
    }

    void onRemoved(const secs::Entity& e) override
    {
        auto& tlc = component<TileComponent>(e);
        m_outputMatrix->set(tlc.previous.x(), tlc.previous.y(), 0);
        m_outputMatrix->set(tlc.current.x(), tlc.current.y(), 0);
    }


private:
    aether::math::Matrix2Di::SharedPtr m_outputMatrix;
    int m_brush;

};


class PlaceEnemyInMapSystem : public PlaceInMapSystem
{
public:

    static constexpr int BRUSH = 2;

    PlaceEnemyInMapSystem( aether::math::Matrix2Di::SharedPtr output_matrix )
        : PlaceInMapSystem( output_matrix, BRUSH )
    {
        addNeededComponents<EnemyComponent>();
    }
};
