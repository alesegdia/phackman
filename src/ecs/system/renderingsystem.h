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

        auto bitmap = render_comp.bitmap;

        float cx = static_cast<float>(bitmap->clip().w()) / 2.f;
        float cy = static_cast<float>(bitmap->clip().h()) / 2.f;

        bitmap->draw(
                    transform_comp.position.x() + cx,
                    transform_comp.position.y() + cy,
                    cx, cy,
                    transform_comp.angle);

    }

};
