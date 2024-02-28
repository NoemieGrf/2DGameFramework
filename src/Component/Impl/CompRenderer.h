#pragma once

#include "SFML/Graphics.hpp"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompRenderer : public ComponentTypeGetter<ComponentType::Renderer>
{
public:
	auto LoadTexture(const std::string& texPath) -> void;
	auto GetRenderBound() const -> vec2f;
	auto GetSprite() -> sf::Sprite&;
	auto SetFlip(bool doFlip) -> void;

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};