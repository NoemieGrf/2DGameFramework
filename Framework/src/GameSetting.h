#pragma once

#include <SFML/Graphics.hpp>

struct GameSetting
{
	//player
	sf::Vector2f playerInitPosition;
	sf::Vector2u playerInitSize;
	float playerInitMoveSpeed;

	// monster
	sf::Vector2f monsterInitPosition;
	sf::Vector2u monsterInitSize;
	float monsterInitMoveSpeed;

};