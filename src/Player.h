#pragma once

// std
#include <string>
// 3rd party
#include "SFML/Graphics.hpp"
// myself
#include "Noncopyable.h"

class Player: Noncopyable
{
public:
	explicit Player(const std::string& pngPath);

public:
	auto SetPosition(const sf::Vector2f& newPos) -> void;
	auto GetPosition() const->const sf::Vector2f&;

	auto SetSize(const sf::Vector2u& size) -> void;
	auto GetSize() const -> const sf::Vector2u&;

	auto SetFlip(bool doFlip) -> void;

	auto SetSpeed(float speed) -> void;
	auto GetSpeed() const -> float;

	auto GetDrawable() const -> const sf::Sprite&;

private:
	sf::Texture _playerTex;
	sf::Sprite _playerSprite;

private: // entity properties
	sf::Vector2f _position;
	sf::Vector2u _size;
	float _speed;
};