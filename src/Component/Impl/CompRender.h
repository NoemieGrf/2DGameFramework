#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "../ComponentTypeGetter.h"
#include "../../Game/GlobalDefine.h"

class CompRender : public ComponentTypeGetter<ComponentType::Render>
{
public:
    virtual auto GetRenderSizeInScreenCoordinate() -> vec2f = 0;
    virtual auto GetSfmlDrawable() -> const sf::Drawable* = 0;
};