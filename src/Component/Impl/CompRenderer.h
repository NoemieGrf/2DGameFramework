#pragma once

#include "SFML/Graphics.hpp"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompRenderer : public ComponentTypeGetter<CompType::Renderer>
{
public:
	explicit CompRenderer(const std::string& texPath);

public:
	auto GetRenderBound() const -> vec2f;
	auto GetSprite() -> sf::Sprite&;
	auto SetFlip(bool doFlip) -> void;

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};