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

public:
	static auto GetInstance() -> Game*;
	static auto GetDeltaTime() -> float;
	static auto GetWindow() -> sf::RenderWindow*;
	static auto GetCamera() -> Camera*;

	template<typename T>
	static auto GetManager() -> T*;

private:
	template<typename T>
	static void AddManager();

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

template<typename T>
void Game::AddManager()
{
	GetInstance()->_gameMgrMap.Add(T::Type(), std::make_unique<T>());
}