#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "IRender.h"

class Player: public IRender
{
public:
	explicit Player(const std::string& pngPath);

public:
	auto SetSize(float width, float height) -> void;
	auto GetSize() const -> sf::Vector2f;
	auto SetPosition(const sf::Vector2f& newPos) -> void;
	auto GetPosition() const -> const sf::Vector2f&;

public:
	auto Render(sf::RenderWindow& rdWindow) -> void override;

private:
	sf::Texture _playerTex;
	sf::Sprite _playerSprite;
};