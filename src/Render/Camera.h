#pragma once

#include "../Game/GlobalDefine.h"
#include "../Utility/Noncopyable.h"

class Camera: public Noncopyable
{
public:
    void DoRender();

private:
    void CalculateCenterAndBound();


private:
    vec2f _currentCenterInWorldCoord;
    vec2f _currentLeftTopInWorldCoord;
    vec2f _currentRightBottomInWorldCoord;
};