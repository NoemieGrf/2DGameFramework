#pragma once

// 3rd
#include "SFML/Window.hpp"
// myself
#include "GlobalDefine.h"
#include "../Utility/Noncopyable.h"
#include "GameSetting.h"
#include "../Entity/Entity.h"

class Game : Noncopyable
{
public:
	void InitConfig();
	void InitWindow();
	void InitScene();

	void Run();

	void Destroy();

public:
	Entity* GetPlayerEntity() const;
	Entity* GetCameraEntity() const;

private:
	uptr<GameSetting> _pGameSetting = nullptr;
	uptr<sf::RenderWindow> _pWindow = nullptr;

	/* All entities in scene */
	umap<uint, sptr<Entity>> _allEntitiesMap = {};

	/* Fast access cache */
	sptr<Entity> _playerEntity = nullptr;
	sptr<Entity> _cameraEntity = nullptr;
};