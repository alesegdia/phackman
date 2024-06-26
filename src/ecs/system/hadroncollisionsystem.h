#pragma once

#include <secs/secs.h>

#include "../components.h"

//#include <allegro5/allegro_primitives.h>

class GameWorld;

class HadronCollisionSystem
        : public secs::TypedEntitySystem<HadronCollisionComponent, TransformComponent>,
          public hadron::ICollisionListener
{
public:

    HadronCollisionSystem()
    {
        SetStepConfiguration(true, true);
        m_physicsWorld.RegisterListener(this);
    }

    ~HadronCollisionSystem()
    {
        m_physicsWorld.UnregisterListener(this);
    }

    void PostUpdate(double delta) override
    {
        SECS_UNUSED(delta);
        m_physicsWorld.Step();
    }

    void process(double delta, const secs::Entity &e, HadronCollisionComponent &hcc, TransformComponent& tc) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        const auto& p = tc.position;
        hcc.body->SetPosition(hadron::Vec2(p.GetX() + hcc.offset.GetX(), p.GetY() + hcc.offset.GetY()));
    }

    void Render(const secs::Entity &e) override
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        const auto& aabb = hcc.body->GetAABB();
        if( enabled )
        {
            aether::graphics::draw_filled_rectangle(aabb.x, aabb.y, aabb.width, aabb.height, aether::graphics::Color(1.0f, 0.0f, 1.0f));
        }
    }

    void OnEntityAdded( const secs::Entity& e )
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        assert(hcc.body != nullptr);
        m_physicsWorld.RegisterBody(hcc.body);
        secs::Entity* eptr = new secs::Entity(e);
        hcc.body->SetUserData(static_cast<void*>(eptr));
    }

    void OnEntityRemoved( const secs::Entity& e )
    {
        auto& hcc = GetComponent<HadronCollisionComponent>(e);
        m_physicsWorld.UnregisterBody(hcc.body);
        auto eptr = static_cast<secs::Entity*>(hcc.body->GetUserData());
        delete eptr;
        delete hcc.body;
        hcc.body = nullptr;
    }

    void OnCollisionEnter(hadron::Body &b1, hadron::Body &b2, hadron::CollisionResult result) override
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        HandleCollision( e1, e2 );
    }

    void OnCollisionExit(hadron::Body &b1, hadron::Body &b2) override
    {
        SECS_UNUSED(b1);
        SECS_UNUSED(b2);
    }

    void HandleCollision( const secs::Entity& e1, const secs::Entity& e2 )
    {
        secs::Entity out1, out2;
        if( entitiesHaveComponents<PlayerInputComponent, CellComponent>(e1, e2, &out1, &out2) && !HasComponent<DieComponent>(out2))
        {
            auto& cell_comp = GetComponent<CellComponent>(out2);
            auto& resources = GetComponent<ResourceStorageComponent>(out1);
            switch(cell_comp.type)
            {
            case CellType::IndustryCell: resources.industryCells++; break;
            case CellType::PowerCell: resources.reinforceCells++; break;
            }
            if (!GetEntityProcessor()->HasComponent<DieComponent>(out2))
            {
                GetEntityProcessor()->AddComponent<DieComponent>(out2);
            }

        }
        else if( entitiesHaveComponents<BulletComponent, EnemyComponent>(e1, e2, &out1, &out2) )
        {
            if (!GetEntityProcessor()->HasComponent<DieComponent>(out1))
            {
                GetEntityProcessor()->AddComponent<DieComponent>(out1);
            }
            auto& dc = GetEntityProcessor()->AddComponent<DamageComponent>(out2);
            dc.damageDone = 1;
            dc.painTimer = 1000000;
        }
        else if( entitiesHaveComponents<PlayerInputComponent, EnemyComponent>(e1, e2, &out1, &out2) )
        {
            auto& hc = GetComponent<HealthComponent>(out1);
            hc.currentHealth = 0;
        }
        else if(entitiesHaveComponents<PlayerInputComponent, CrucibleComponent>(e1, e2, &out1, &out2))
        {
            m_playerEscaped = GetComponent<AgentInputComponent>(out1).carryCrucible;
        }
    }

    bool DidPlayerEscape()
    {
	    return m_playerEscaped;
    }

private:

    template <typename C1, typename C2>
    bool entitiesHaveComponents(secs::Entity e1, secs::Entity e2, secs::Entity* ref1, secs::Entity* ref2)
    {
        bool check = false;
        if( HasComponent<C1>(e1) && HasComponent<C2>(e2) )
        {
            *ref1 = e1; *ref2 = e2;
            check = true;
        }
        else if( HasComponent<C1>(e2) && HasComponent<C2>(e1) )
        {
            *ref1 = e2; *ref2 = e1;
            check = true;
        }
        return check;
    }

    secs::Entity getEntityFromBody( hadron::Body& b )
    {
        return *(static_cast<secs::Entity*>(b.GetUserData()));
    }

    hadron::collision::World m_physicsWorld;

    bool enabled = false;

    bool m_playerEscaped = false;

};
