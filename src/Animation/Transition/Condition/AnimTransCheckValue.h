#pragma once

#include "AnimTransCondition.h"

class AnimTransCheckValue: public AnimTransCondition
{
public:
    enum class OperationType
    {
        GreaterThan,
        LessThan,
        Equal
    };

    enum class SourceType
    {
        HorizontalVelocity,
        VerticalVelocity
    };

public:
    AnimTransCheckValue(OperationType opType, SourceType srcType, float targetValue);

public:
    bool Check(Entity* pEntity) override;

private:
    bool ValueCheck(float source, float target);

private:
    OperationType _operationType;
    SourceType _sourceType;
    float _targetValue;
};