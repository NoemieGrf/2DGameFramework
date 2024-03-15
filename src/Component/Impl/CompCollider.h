#pragma once

#include "Game/GlobalDefine.h"
#include "Component/ComponentTypeGetter.h"
#include "Manager/Impl/PhysicsManager.h"
#include "Config/GlobalSetting.h"

class CompCollider: public ComponentTypeGetter<ComponentType::Collider>
{
public:
    enum class Tag
    {
        Entity,
        Ground
    };

public:
    auto Init(bool isDynamic, const vec2f& aabbBox, const PhysicsFixture& fixture, Tag tag) -> void;
    auto GetPhysicsBody() const -> b2Body*;
    auto GetPhysicalWorldPosition() const -> vec2f;
    auto SetPhysicalWorldPosition(const vec2f& pos) -> void;
    auto ApplyForce(const vec2f& force) -> void;
    auto ApplyImpulse(const vec2f& impulse) -> void;
    auto SetVelocity(const vec2f& veclocity) -> void;
    auto GetVelocity() const -> vec2f;
    auto GetTag() const -> Tag;

public:
    std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter> _pPhyBody = nullptr;
    Tag _tag;
};