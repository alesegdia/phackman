#pragma once

#include <secs/secs.h>
#include "../components.h"

class ComputeTileSystem : public secs::TypedEntitySystem<TileComponent, TransformComponent>
{
public:
    void process(double delta, const secs::Entity &e, TileComponent &tlc, TransformComponent& trc)
    {
        SECS_UNUSED(e);
        SECS_UNUSED(delta);
        computeTile( tlc, trc );
    }

    void onAdded( const secs::Entity& e )
    {
        auto& tlc = component<TileComponent>(e);
        auto& tc = component<TransformComponent>(e);
        computeTile(tlc, tc);
    }

private:
    void computeTile( TileComponent& tlc, TransformComponent& trc )
    {
        int tx, ty;
        tx = (trc.position.x() + 16) / 32;
        ty = (trc.position.y() + 16) / 32;
        tlc.previous = tlc.current;
        tlc.current.set( tx, ty );
    }

};
