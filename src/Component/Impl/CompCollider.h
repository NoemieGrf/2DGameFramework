#pragma once

#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"
#include "../../Manager/Impl/PhysicsManager.h"

class CompCollider: public ComponentTypeGetter<ComponentType::Collider>
{
public:
    auto Init(bool isDynamic, const vec2f& aabbBox) -> void;
    auto GetPhysicalWorldPosition() const -> vec2f;
    auto SetPhysicalWorldPosition(const vec2f& pos) -> void;
    auto ApplyForce(const vec2f& force) -> void;
    auto ApplyImpulse(const vec2f& impulse) -> void;
    auto SetVelocity(const vec2f& veclocity) -> void;
    auto GetVelocity() const -> vec2f;

public:
    std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter> _pPhyBody = nullptr;

};