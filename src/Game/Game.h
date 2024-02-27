#pragma once

// 3rd
#include "SFML/Graphics/RenderWindow.hpp"
// myself
#include "GlobalDefine.h"
#include "Manager/GameManager.h"
#include "Manager/GameManagerType.h"
#include "GameSetting.h"
#include "../Entity/Entity.h"
#include "../Render/Camera.h"
#include "../Utility/OrderedHashMap.hpp"

class Game : Noncopyable
{
private:
	Game();

public:
	void InitConfig();
	void InitWindow();
	void InitScene();

	void GameLoop();

	void Destroy();

private: 
	void UpdateTime();
	void UpdateWindowEvent();
	void UpdateUserInput();
	void UpdateAI();
	void UpdatePhysics();
	void RenderScene();

public:
	auto GetWindow() const -> sf::RenderWindow*;
	auto GetPlayerEntity() const -> Entity*;
	auto GetDeltaTime() const -> float;
	auto GetCamera() const -> Camera*;
	auto GetAllEntities() const -> const umap<uint, sptr<Entity>>&;

private:
	uptr<GameSetting> _pGameSetting = nullptr;
	uptr<sf::RenderWindow> _pWindow = nullptr;

	/* Manager */
	OrderedHashMap<GameManagerType, uptr<GameManager>> _gameMgrMap;

	/* Game clock */
	sf::Clock _clock;
	float _deltaTimeSecond;

	/* Game camera */
	uptr<Camera> _pMainCamera = nullptr;

	/* All entities in scene */
	umap<uint, sptr<Entity>> _allEntitiesMap = {};

	/* Fast access cache */
	sptr<Entity> _playerEntity = nullptr;

public:
	static Game* GetInstance();
};