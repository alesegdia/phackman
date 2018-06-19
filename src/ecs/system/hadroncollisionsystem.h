#pragma once

#include <secs/secs.h>

#include "../component/components.h"

#include <allegro5/allegro_primitives.h>

class HadronCollisionSystem
        : public secs::TypedEntitySystem<HadronCollisionComponent, TransformComponent>,
          public hadron::collision::ICollisionListener
{
public:

    HadronCollisionSystem()
    {
        setStepConfiguration(true, true);
        m_physicsWorld.registerListener(this);
    }

    ~HadronCollisionSystem()
    {
        m_physicsWorld.unregisterListener(this);
    }

    void postUpdate(double delta) override
    {
        m_physicsWorld.step();
    }

    void process(double delta, const secs::Entity &e, HadronCollisionComponent &hcc, TransformComponent& tc) override
    {
        const auto& p = tc.position;
        hcc.body->setPosition(hadron::math::Vec2(p.x() + hcc.offset.x(), p.y() + hcc.offset.y()));
    }

    void render(const secs::Entity &e) override
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        const auto& aabb = hcc.body->aabb();
        float x1, y1, x2, y2;
        x1 = aabb.x;
        x2 = x1 + aabb.width;
        y1 = aabb.y;
        y2 = y1 + aabb.height;
        //al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 255), 2.f );
    }

    void onAdded( const secs::Entity& e )
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        assert(hcc.body != nullptr);
        m_physicsWorld.registerBody(hcc.body);
        secs::Entity* eptr = new secs::Entity(e);
        hcc.body->userData(static_cast<void*>(eptr));
    }

    void onRemoved( const secs::Entity& e )
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        m_physicsWorld.unregisterBody(hcc.body);
        auto eptr = static_cast<secs::Entity*>(hcc.body->userData());
        delete eptr;
        delete hcc.body;
        hcc.body = nullptr;
        printf("cleanup\n"); fflush(0);
    }

    void onCollisionEnter(hadron::collision::Body &b1, hadron::collision::Body &b2)
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        handleCollision( e1, e2 );
    }

    void handleCollision( const secs::Entity& e1, const secs::Entity& e2 )
    {
        if( hasComponent<KeyboardInputComponent>(e1) && hasComponent<CellComponent>(e2) )
        {
            /*
            auto& cell_comp = component<CellComponent>(cell);
            switch(cell_comp)
            {
            case CellType::IndustryCell: cell_comp.industry++;
            case CellType::PowerCell: cell_comp.power++;
            }
            addComponent<DieComponent>(cell);
            */
            processor()->removeEntity(e2);
        }
    }

private:

    secs::Entity getEntityFromBody( hadron::collision::Body& b )
    {
        return *(static_cast<secs::Entity*>(b.userData()));
    }

    hadron::collision::World m_physicsWorld;


};
