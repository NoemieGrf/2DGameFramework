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
	auto GetRenderSizeInScreenCoordinate() -> vec2f override;
	auto GetSfmlDrawable() -> const sf::Drawable* override;

private:
	uptr<sf::Sprite> _pSprite = nullptr;
};
