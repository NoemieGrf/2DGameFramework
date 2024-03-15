#pragma once

#include "AnimTransCondition.h"

class AnimTransCheckState: public AnimTransCondition
{
public:
    enum class StateType
    {
        OnAir,
    };

public:
    AnimTransCheckState(StateType type, int targetValue);

public:
    bool Check(Entity* pEntity) override;

private:
    bool GetOnAirState(Entity* pEntity) const;

private:
    StateType _type;
    int _targetValue;
};