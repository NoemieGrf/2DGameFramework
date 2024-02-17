#pragma once

#include <SFML/Graphics.hpp>

class IRender
{
public:
	virtual void Render(sf::RenderWindow& rdWindow) = 0;
};

