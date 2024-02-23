#pragma once

#include "SFML/Graphics.hpp"
#include "ComponentTypeGetter.h"

class CompRenderer : public ComponentTypeGetter<CompType::Renderer>
{
public:
	explicit CompRenderer(const std::string& texPath);

public:
	const sf::Sprite& GetSprite() const;

	void SetFlip(bool doFlip);

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};