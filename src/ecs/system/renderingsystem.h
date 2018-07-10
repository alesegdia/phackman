#pragma once

#include <secs/secs.h>
#include "../components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

    RenderingSystem()
    {
        setStepConfiguration(false, true);
        setNeededComponents<RenderComponent, TransformComponent>();
    }

    void render( const secs::Entity &e) override
    {
        auto& render_comp = component<RenderComponent>(e);
        auto& transform_comp = component<TransformComponent>(e);

        assert(render_comp.bitmap != nullptr);

        ALLEGRO_BITMAP* bitmap = render_comp.bitmap;

        float cx = static_cast<float>(al_get_bitmap_width(bitmap)) / 2.f;
        float cy = static_cast<float>(al_get_bitmap_height(bitmap)) / 2.f;

        al_draw_rotated_bitmap(
                    bitmap, cx, cy,
                    transform_comp.position.x() + cx,
                    transform_comp.position.y() + cy,
                    transform_comp.angle, 0 );

    }

};
