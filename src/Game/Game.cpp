#include "Game.h"

// std
#include <memory>
// 3rd party
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
// myself
#include "../Manager/Impl/AiManager.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Manager/Impl/SceneManager.h"
#include "../Manager/Impl/UserInputManager.h"
#include "../Manager/Impl/PhysicsManager.h"

Game::Game() = default;

void Game::Init()
{
    // init window
    using uint = unsigned int;
    uint screenHeight = sf::VideoMode::getDesktopMode().height;
    uint screenWidth = sf::VideoMode::getDesktopMode().width;
    uint windowSize = 0.7 * std::min(screenHeight, screenWidth);
    _pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize, windowSize), "2DGame");

    // create game manager
    AddManager<ConfigManager>();
    AddManager<UserInputManager>();
    AddManager<SceneManager>();
    AddManager<AiManager>();
    AddManager<PhysicsManager>();

    // create level
    GetManager<SceneManager>()->InitLevel();
}

void Game::GameLoop()
{
    _clock.restart();

    while (_pWindow->isOpen())
    {
        // window event
        sf::Event event;
        while (_pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _pWindow->close();
                continue;
            }
        }

        // update game time
        sf::Time deltaTime = _clock.getElapsedTime();
        _clock.restart();
        _deltaTimeSecond = deltaTime.asSeconds();
        
        // update all manager
        for (auto mgrType: _gameMgrMap)
            _gameMgrMap[mgrType]->PreTick();

        for (auto mgrType: _gameMgrMap)
            _gameMgrMap[mgrType]->Tick();

        for (auto mgrType: _gameMgrMap)
            _gameMgrMap[mgrType]->LateTick();

        // render scene
        _pWindow->clear(sf::Color::White);
        _pMainCamera->DoRender();
        _pWindow->display();
    }
}

void Game::Destroy()
{
}

Game* Game::GetInstance()
{
    static Game* pGame = new Game();
    return pGame;
}

sf::RenderWindow* Game::GetWindow()
{
    return GetInstance()->_pWindow.get();
}

Camera* Game::GetCamera()
{
    return GetInstance()->_pMainCamera.get();
}

float Game::GetDeltaTime()
{
    return GetInstance()->_deltaTimeSecond;
}
