#pragma once

#include <string>
#include "../Game/GlobalDefine.h"

struct GlobalSetting
{
    float globalGravity;
    std::string levelMapPath;
    std::string levelWallTexPath;
    vec2f cameraRectWorldCoordinateSize;
};