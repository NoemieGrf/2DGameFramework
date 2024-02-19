#pragma once

// std
#include <memory>
// 3rd
#include "SFML/Window.hpp"
// myself
#include "Noncopyable.h"
#include "GameSetting.h"
#include "Player.h"

class Game : Noncopyable
{
public:
	void InitConfig();
	void InitWindow();
	void InitScene();

	void Run();

	void Destroy();

private:
	std::unique_ptr<GameSetting> _pGameSetting = nullptr;
	std::unique_ptr<sf::RenderWindow> _pWindow = nullptr;
	std::unique_ptr<Player> _pPlayer = nullptr;
};