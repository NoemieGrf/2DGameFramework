#pragma once

// std
#include <string>
// 3rd party
#include "SFML/Graphics.hpp"
// myself
#include "GlobalDefine.h"
#include "Noncopyable.h"

class Monster : Noncopyable
{
public:
	explicit Monster(const std::string& pngPath, uint id);

public: 
	auto GetId() const -> uint;

	auto SetPosition(const sf::Vector2f& newPos) -> void;
	auto GetPosition() const->const sf::Vector2f&;

	auto SetSize(const sf::Vector2u& size) -> void;
	auto GetSize() const -> const sf::Vector2u&;

	auto SetFlip(bool doFlip) -> void;

	auto SetSpeed(float speed) -> void;
	auto GetSpeed() const -> float;

	auto GetDrawable() const -> const sf::Sprite&;

private:
	sf::Texture _monsterTex;
	sf::Sprite _monsterSprite;

private: // entity properties
	uint _id;
	sf::Vector2f _position;
	sf::Vector2u _size;
	float _speed;
};