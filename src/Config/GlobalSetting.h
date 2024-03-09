#pragma once

#include <string>
#include "../Game/GlobalDefine.h"

struct PhysicsFixture
{
    float density;
    float friction;
    float restitution;
};

struct GlobalSetting
{
    float globalGravity;
    std::string levelMapPath;
    std::string levelWallTexPath;
    vec2f cameraRectWorldCoordinateSize;
    PhysicsFixture entityPhysicsFixture;
    PhysicsFixture wallPhysicsFixture;
};