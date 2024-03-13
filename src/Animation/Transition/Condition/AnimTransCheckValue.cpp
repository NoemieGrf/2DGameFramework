#include "AnimTransCheckValue.h"

#include <format>
#include "Entity/Entity.h"
#include "Component/Impl/CompCollider.h"
#include "Utility/Logger.h"
#include "Utility/Util.hpp"

AnimTransCheckValue::AnimTransCheckValue(OperationType opType, SourceType srcType, float targetValue)
    : _operationType(opType)
    , _sourceType(srcType)
    , _targetValue(targetValue)
{
}

bool AnimTransCheckValue::Check(Entity* pEntity)
{
    const CompCollider* pCollider = pEntity->GetComponent<CompCollider>();
    if (pCollider == nullptr)
    {
        Logger::LogError(std::format("[Anim] {} do not have collider!", pEntity->GetName()));
        return false;
    }

    vec2f velocity = pCollider->GetVelocity();

    switch (_sourceType) 
    {
    case SourceType::HorizontalVelocity:
        return ValueCheck(abs(velocity.x), _targetValue);
    case SourceType::VerticalVelocity:
        return ValueCheck(abs(velocity.y), _targetValue);
    }
}

bool AnimTransCheckValue::ValueCheck(float source, float target)
{
    switch (_operationType) 
    {
    case OperationType::GreaterThan:
        return source > target;
    case OperationType::LessThan:
        return source < target;
    case OperationType::Equal:
        return Util::NearZero(source - target);
    }
}