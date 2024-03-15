#include "AnimTransCheckState.h"
#include "Game/Game.h"
#include "Entity/Entity.h"
#include "Manager/Impl/PhysicsManager.h"
#include "Component/Impl/CompCollider.h"
#include "Manager/Impl/PhysicsManager.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world_callbacks.h"

AnimTransCheckState::AnimTransCheckState(AnimTransCheckState::StateType type, int targetValue)
    : _type(type)
    , _targetValue(targetValue)
{
}

bool AnimTransCheckState::Check(Entity* pEntity) 
{
    switch (_type) 
    {
    case StateType::OnAir:
        bool isOnAir = GetOnAirState(pEntity);
        return isOnAir ? (_targetValue == 1): (_targetValue == 0);
    }
}

bool AnimTransCheckState::GetOnAirState(Entity* pEntity) const
{
    if (pEntity == nullptr)
        return false;

    CompCollider* pCollider = pEntity->GetComponent<CompCollider>();
    if (pCollider == nullptr)
        return false;

    vec2f startPosition = pCollider->GetPhysicalWorldPosition();
    vec2f endPosition = startPosition - vec2f { 0, 20 };

    struct RayCastCallback: b2RayCastCallback
    {
        bool* pTargetOnGround;
        b2Body* pEntityPhyBody;

        float ReportFixture(b2Fixture* pTargetFixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override
        {
            b2Body* pTargetBody = pTargetFixture->GetBody();
            CompCollider* pCollider = Game::GetManager<PhysicsManager>()->GetColliderFromBody(pTargetBody);
            if (pCollider == nullptr)
                return true;    // keep ray casting

            if (pCollider->GetTag() == CompCollider::Tag::Ground)
            {
                b2ContactEdge* pEdge = pEntityPhyBody->GetContactList();
                while (pEdge != nullptr)
                {
                    b2Contact* pContact = pEdge->contact;
                    b2Fixture* pFixture1 = pContact->GetFixtureA();
                    b2Fixture* pFixture2 = pContact->GetFixtureB();

                    if (pFixture1 == pTargetFixture || pFixture2 == pTargetFixture)
                    {
                        *pTargetOnGround = true;
                        return false;
                    }

                    pEdge = pEdge->next;
                }

            }

            return true; 
        }
    };

    bool entityOnGround = false;
    RayCastCallback rayCastCallback;
    rayCastCallback.pTargetOnGround = &entityOnGround;
    rayCastCallback.pEntityPhyBody = pCollider->GetPhysicsBody();

    b2World* pPhyWorld = Game::GetManager<PhysicsManager>()->GetPhysicWorld();
    pPhyWorld->RayCast(&rayCastCallback, 
        b2Vec2 { startPosition.x, startPosition.y }, 
        b2Vec2 { endPosition.x, endPosition.y });

    return entityOnGround;
}