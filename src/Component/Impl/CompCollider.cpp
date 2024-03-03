#include "CompCollider.h"
#include "../../Game/Game.h"

void CompCollider::Init()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);

    b2Body* _pPhyBodyRaw = Game::GetManager<PhysicsManager>()->GetPhysicWorld()->CreateBody(&bodyDef);
    _pPhyBody = std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter>(_pPhyBodyRaw);
}