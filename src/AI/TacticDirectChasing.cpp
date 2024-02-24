#include "TacticDirectChasing.h"
#include "../Game/Game.h"
#include "../Utility/Util.hpp"

void TacticDirectChasing::SetChasingTarget(const CompTransform* pTarget)
{
    _chasingTarget = pTarget;
}

void TacticDirectChasing::SetChasingTarget(const Entity* pTarget)
{
    SetChasingTarget(pTarget->GetComponent<CompTransform>());
}

void TacticDirectChasing::SetChasingSpeed(float value)
{
    _chasingSpeed = value;
}

vec2f TacticDirectChasing::UpdatePosition(const vec2f& inputPos) const
{
    if (_chasingTarget == nullptr)
        return inputPos;

    vec2f direction = Util::Normalize(_chasingTarget->GetPosition() - inputPos);
    return inputPos + direction * _chasingSpeed * Game::GetInstance()->GetDeltaTime();
}