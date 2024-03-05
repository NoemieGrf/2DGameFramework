#include "CompCollider.h"
#include "../../Game/Game.h"
#include "../../Entity/Entity.h"
#include "CompTransform.h"

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

    b2Body* _pPhyBodyRaw = Game::GetManager<PhysicsManager>()->GetPhysicWorld()->CreateBody(&bodyDef);
    _pPhyBody = std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>(_pPhyBodyRaw);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(aabbBox.x, aabbBox.y);    // box size

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f; // 设置密度，影响物体的质量
    fixtureDef.friction = 0.3f; // 设置摩擦系数
    fixtureDef.restitution = 0.0f;  // 设置弹性

    _pPhyBody->CreateFixture(&fixtureDef);
}