#pragma once

#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "CompRender.h"

class CompSprite : public CompRender
{
public:
	auto Load(const std::string& texPath, const vec2f& sizeInScreen) -> void;
	auto GetSprite() -> sf::Sprite*;

public:
	auto GetRenderSizeInScreenCoordinate() -> vec2f override;

private:
	uptr<sf::Sprite> _pSprite = nullptr;
};
