#include "AnimTransCheckProgress.h"

#include <format>
#include "Entity/Entity.h"
#include "Component/Impl/CompSpine.h"
#include "Utility/Logger.h"

AnimTransCheckProgress::AnimTransCheckProgress(float ratio)
    : _ratio(ratio)
{
}

bool AnimTransCheckProgress::Check(Entity* pEntity)
{
    CompSpine* pSpine = pEntity->GetComponent<CompSpine>();
    if (pSpine == nullptr)
    {
        Logger::LogError(std::format("[Anim] {} do not have spine!", pEntity->GetName()));
        return false;
    }

    float currentProgress = pSpine->GetCurrentAnimProgress();
    return currentProgress >= _ratio;
}