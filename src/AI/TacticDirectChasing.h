#pragma once

#include "Tactic.h"
#include "../Component/Impl/CompTransform.h"
#include "../Entity/Entity.h"

class TacticDirectChasing: public Tactic
{
public:
    auto SetChasingTarget(const CompTransform* pTarget) -> void;
    auto SetChasingTarget(const Entity* pEntity) -> void;
    auto SetChasingSpeed(float value) -> void;

    auto UpdatePosition(const vec2f& inputPos) const -> vec2f;

private:
    float _chasingSpeed = 120.0f;
    const CompTransform* _chasingTarget = nullptr;
};