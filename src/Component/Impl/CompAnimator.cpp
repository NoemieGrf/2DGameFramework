#include "CompAnimator.h"
#include "CompSpine.h"
#include "CompCollider.h"
#include "../../Game/Game.h"
#include "../../Manager/Impl/UserInputManager.h"
#include "../../Utility/Util.hpp"
#include "../../Entity/Entity.h"

void CompAnimator::Update()
{

}

void CompAnimator::EnqueueTrigger(const std::string& trigger)
{
    _animTriggers.push(trigger);
}

std::optional<std::string> CompAnimator::DequeueTrigger()
{
    if (_animTriggers.empty())
        return std::nullopt;

    std::string result = _animTriggers.front();
    _animTriggers.pop();
    return result;
}