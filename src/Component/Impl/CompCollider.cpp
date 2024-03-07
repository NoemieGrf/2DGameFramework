#include "CompCollider.h"
#include "../../Game/Game.h"
#include "../../Entity/Entity.h"
#include "CompTransform.h"
#include "box2d/b2_math.h"

void CompCollider::Init(bool isDynamic, const vec2f& aabbBox)
{
    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody: b2_staticBody;
    bodyDef.fixedRotation = true;

    const CompTransform* pEntityTrans = GetEntity()->GetComponent<CompTransform>();
    if (pEntityTrans != nullptr)
    {
        auto transWorldPos = pEntityTrans->GetPosition();
        bodyDef.position.Set(transWorldPos.x, transWorldPos.y); // todo move to center
    }
    else
        bodyDef.position.Set(0.0f, 0.0f);

    _pPhyBody = Game::GetManager<PhysicsManager>()->CreatePhysicBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(aabbBox.x, aabbBox.y);    // box size

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f; // 设置密度，影响物体的质量
    fixtureDef.friction = 0.3f; // 设置摩擦系数
    fixtureDef.restitution = 0.0f;  // 设置弹性

    _pPhyBody->CreateFixture(&fixtureDef);
}

vec2f CompCollider::GetPhysicalWorldPosition() const
{
    b2Vec2 pos = _pPhyBody->GetPosition();
    return vec2f { pos.x, pos.y };
}

void CompCollider::SetPhysicalWorldPosition(const vec2f& pos)
{
    _pPhyBody->SetTransform(b2Vec2 { pos.x, pos.y }, 0);
}

void CompCollider::ApplyForce(const vec2f& force)
{
    _pPhyBody->ApplyForceToCenter(b2Vec2{ force.x, force.y }, true);
}

void CompCollider::ApplyImpulse(const vec2f& impulse)
{
    _pPhyBody->ApplyLinearImpulseToCenter(b2Vec2{ impulse.x, impulse.y }, true);
}