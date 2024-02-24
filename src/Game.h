#pragma once

// 3rd
#include "SFML/Window.hpp"
// myself
#include "GlobalDefine.h"
#include "Noncopyable.h"
#include "GameSetting.h"
#include "Player.h"
#include "Monster.h"

class Game : Noncopyable
{
public:
	void InitConfig();
	void InitWindow();
	void InitScene();

	void Run();

	void Destroy();

private:
	uptr<GameSetting> _pGameSetting = nullptr;
	uptr<sf::RenderWindow> _pWindow = nullptr;
	uptr<Player> _pPlayer = nullptr;
	umap<uint, uptr<Monster>> _pMonsters = {};
};