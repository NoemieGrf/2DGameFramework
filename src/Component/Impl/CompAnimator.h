#pragma once

#include "../ComponentTypeGetter.h"

class CompAnimator : public ComponentTypeGetter<ComponentType::Animator>
{
public:
    void Update();

private:
    enum HorizontalMoveState
    {
        RunLeft,
        Idle,
        RunRight
    };

private:
    HorizontalMoveState _lastFrameHorizontalMoveState = HorizontalMoveState::Idle;
    
};