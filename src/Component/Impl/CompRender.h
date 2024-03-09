#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "../ComponentTypeGetter.h"
#include "../../Game/GlobalDefine.h"

class CompRender : public ComponentTypeGetter<ComponentType::Render>
{
public:
    virtual auto GetRenderSizeInScreenCoordinate() const -> vec2f = 0;
    virtual auto GetSfmlDrawable() const -> sf::Drawable* = 0;
    virtual auto SetSfmlDrawableScreenCoordinate(const vec2f& coord) -> void = 0;
    virtual auto SetFlip(bool doFlip) -> void = 0;
};