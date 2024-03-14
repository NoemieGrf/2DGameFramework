#include "AnimTransCheckTrigger.h"
#include "Entity/Entity.h"
#include "Component/Impl/CompAnimator.h"

AnimTransCheckTrigger::AnimTransCheckTrigger(const std::string& targetTrigger)
    : _targetTrigger(targetTrigger)
{
}

bool AnimTransCheckTrigger::Check(Entity* pEntity) 
{
    CompAnimator* pAnimator = pEntity->GetComponent<CompAnimator>();
    if (pAnimator == nullptr)
        return false;

    auto trigger = pAnimator->DequeueTrigger();
    if (!trigger.has_value())
        return false;

    return trigger.value() == _targetTrigger;
}