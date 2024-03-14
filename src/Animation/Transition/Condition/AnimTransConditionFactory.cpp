#include <format>
#include "AnimTransConditionFactory.h"
#include "AnimTransCheckProgress.h"
#include "AnimTransCheckState.h"
#include "AnimTransCheckValue.h"
#include "AnimTransCheckTrigger.h"
#include "Utility/Logger.h"


uptr<AnimTransCondition> AnimTransCheckerFactory::CreateValueChecker(
    const std::string& operationType, 
    const std::string& sourceType, 
    float targetValue)
{
    AnimTransCheckValue::OperationType op;
    if (operationType == "greaterThan")
        op = AnimTransCheckValue::OperationType::GreaterThan;
    else if (operationType == "lessThan")
        op = AnimTransCheckValue::OperationType::LessThan;
    else if (operationType == "equal")
        op = AnimTransCheckValue::OperationType::Equal;
    else
        Logger::LogError(std::format("[AnimTransCheckValue] No operation type: {}", operationType));

    AnimTransCheckValue::SourceType src;
    if (sourceType == "horizontalVelocity")
        src = AnimTransCheckValue::SourceType::HorizontalVelocity;
    else if (sourceType == "verticalVelocity")
        src = AnimTransCheckValue::SourceType::VerticalVelocity;
    else
        Logger::LogError(std::format("[AnimTransCheckValue] No source type: {}", sourceType));

    return std::make_unique<AnimTransCheckValue>(op, src, targetValue);
}

uptr<AnimTransCondition> AnimTransCheckerFactory::CreateProgressChecker(float progress)
{
    return std::make_unique<AnimTransCheckProgress>(progress);
}

uptr<AnimTransCondition> AnimTransCheckerFactory::CreateTriggerChecker(const std::string& triggerName)
{
    return std::make_unique<AnimTransCheckTrigger>(triggerName);
}

uptr<AnimTransCondition> AnimTransCheckerFactory::CreateStateChecker(const std::string& state, int value)
{
    AnimTransCheckState::StateType stateType;
    if (state == "onAir")
        stateType = AnimTransCheckState::StateType::OnAir;
    else
        Logger::LogError(std::format("[AnimTransCheckState] No state type: {}", state));

    return std::make_unique<AnimTransCheckState>(stateType, value);
}