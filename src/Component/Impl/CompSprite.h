#pragma once

#include "SFML/Graphics.hpp"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompSprite : public ComponentTypeGetter<ComponentType::SpriteRender>
{
public:
	auto Load(const std::string& texPath) -> void;
	auto GetSprite() -> sf::Sprite*;

private:
	uptr<sf::Sprite> _pSprite = nullptr;
};
