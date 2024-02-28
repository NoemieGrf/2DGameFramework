#pragma once

// 3rd
#include "SFML/Graphics/RenderWindow.hpp"
// myself
#include "GlobalDefine.h"
#include "../Manager/GameManager.h"
#include "../Manager/GameManagerType.h"
#include "../Entity/Entity.h"
#include "../Render/Camera.h"
#include "../Utility/OrderedHashMap.hpp"

class Game : Noncopyable
{
private:
	Game();

public:
	void Init();
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
	/* Window */
	uptr<sf::RenderWindow> _pWindow = nullptr;

	/* Game clock */
	sf::Clock _clock;
	float _deltaTimeSecond;

	/* Manager */
	OrderedHashMap<GameManagerType, uptr<GameManager>> _gameMgrMap;

	/* Game camera */
	uptr<Camera> _pMainCamera = nullptr;

public:
	static Game* GetInstance();

	template<typename T>
	static T* GetManager();
};

template<typename T>
T* Game::GetManager()
{
	auto& mgrMap = GetInstance()->_gameMgrMap;
	GameManagerType t = T::Type();
	if (!mgrMap.Contains(t))
		return nullptr;

	return dynamic_cast<T>(mgrMap[t].get());
}