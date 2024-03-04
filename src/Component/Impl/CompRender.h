#pragma once

#include "../ComponentTypeGetter.h"
#include "../../Game/GlobalDefine.h"

class CompRender : public ComponentTypeGetter<ComponentType::Render>
{
public:
    virtual auto GetRenderSizeInScreenCoordinate() -> vec2f = 0;

};