#pragma once

#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "CompRender.h"

class CompSprite : public CompRender
{
public:
	auto Load(const std::string& texPath) -> void;
	auto GetSprite() -> sf::Sprite*;

public:
	auto GetRenderSizeInScreenCoordinate() const -> vec2f override;
	auto GetSfmlDrawable() const -> sf::Drawable* override;
	auto SetSfmlDrawableScreenCoordinate(const vec2f& coord) -> void override;

private:
	uptr<sf::Sprite> _pSprite = nullptr;
};
