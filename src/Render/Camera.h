#pragma once

#include "../Game/GlobalDefine.h"
#include "../Utility/Noncopyable.h"

class Camera: public Noncopyable
{
public:
    void DoRender();

private:
    void SetCurrentScreenSize();
    void CalculateCenterAndBound();

private: // helper
    vec2f WorldCoordToScreenCoord(const vec2f& worldPos);

private:
    vec2f _currentScreenSize;
    vec2f _currentCenterInWorldCoord;
    vec2f _currentLeftBottomInWorldCoord;
    vec2f _currentRightTopInWorldCoord;
    
};