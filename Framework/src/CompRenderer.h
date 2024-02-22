#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"

class CompRenderer : public Component
{
public:
	explicit CompRenderer(const std::string& texPath);

public: // override
	CompType GetType() const override;

public:
	const sf::Sprite& GetSprite() const;

	void SetFlip(bool doFlip);

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};