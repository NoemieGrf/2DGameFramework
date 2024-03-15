#include "AnimTransCheckTrigger.h"
#include "Entity/Entity.h"
#include "Component/Impl/CompSpine.h"

AnimTransCheckTrigger::AnimTransCheckTrigger(const std::string& targetTrigger)
    : _targetTrigger(targetTrigger)
{
}

bool AnimTransCheckTrigger::Check(Entity* pEntity) 
{
    CompSpine* pSpine = pEntity->GetComponent<CompSpine>();
    if (pSpine == nullptr)
        return false;

    auto trigger = pSpine->DequeueAnimTrigger();
    if (!trigger.has_value())
        return false;

    return trigger.value() == _targetTrigger;
}