#include "AnimTransCheckState.h"

AnimTransCheckState::AnimTransCheckState(AnimTransCheckState::StateType type, int targetValue)
    : _type(type)
    , _targetValue(targetValue)
{
}

bool AnimTransCheckState::Check(Entity* pEntity) 
{
    switch (_type) 
    {
    case StateType::OnAir:
      break;
    }
}