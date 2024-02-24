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

    vec2f direction = _chasingTarget->GetPosition() - inputPos;
    float distanceMag = direction.x * direction.x + direction.y * direction.y;
    if (distanceMag < 350 * 350)
        return inputPos - Util::Normalize(direction) * (_chasingSpeed / 2) * Game::GetInstance()->GetDeltaTime();
    else
        return inputPos + Util::Normalize(direction) * _chasingSpeed * Game::GetInstance()->GetDeltaTime();;
}