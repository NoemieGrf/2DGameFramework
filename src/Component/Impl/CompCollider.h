#pragma once

#include "box2d/box2d.h"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"
#include "../../Manager/Impl/PhysicsManager.h"

class CompCollider: public ComponentTypeGetter<ComponentType::Collider>
{
public:
    auto Init() -> void;

public:
    std::unique_ptr<b2Body, PhysicsManager::B2BodyDeleter> _pPhyBody = nullptr;

};