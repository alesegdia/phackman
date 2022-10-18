#pragma once

#include <secs/secs.h>
#include "../components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

    RenderingSystem()
    {
        SetStepConfiguration(false, true);
        SetNeededComponents<RenderComponent, TransformComponent>();
    }

    void Render( const secs::Entity &e) override
    {
        auto& render_comp = GetComponent<RenderComponent>(e);
        auto& transform_comp = GetComponent<TransformComponent>(e);

        assert(render_comp.bitmap.IsValid());

        auto bitmap = render_comp.bitmap;

        float cx = static_cast<float>(bitmap.GetClip().w()) / 2.f;
        float cy = static_cast<float>(bitmap.GetClip().h()) / 2.f;

        bitmap.Draw(
                    transform_comp.position.GetX() + cx,
                    transform_comp.position.GetY() + cy,
                    cx, cy,
                    transform_comp.angle);

    }

};
