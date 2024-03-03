#pragma once

#include "SFML/Graphics.hpp"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompSprite : public ComponentTypeGetter<ComponentType::SpriteRender>
{
public:
	auto LoadTexture(const std::string& texPath) -> void;

	auto GetSprite() -> sf::Sprite&;
	auto SetFlip(bool doFlip) -> void;

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};
