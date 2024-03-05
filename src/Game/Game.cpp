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
#include "../Manager/Impl/ResourceManager.h"
#include "../Manager/Impl/SceneManager.h"
#include "../Manager/Impl/UserInputManager.h"
#include "../Manager/Impl/PhysicsManager.h"
#include "../Manager/Impl/AnimationManager.h"
#include "SFML/Window/WindowStyle.hpp"

Game::Game() = default;

void Game::Init()
{
    // init window
    _pWindow = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(800, 600), 
        "2DGame",
        sf::Style::Titlebar | sf::Style::Close  // no resize
        );

    _pWindow->setFramerateLimit(60);

    // create camera
    _pMainCamera = std::make_unique<Camera>();

    // create game manager, order is really important!
    AddManager<ConfigManager>();
    AddManager<ResourceManager>();
    AddManager<PhysicsManager>();
    AddManager<UserInputManager>();
    AddManager<SceneManager>();
    AddManager<AiManager>();
    AddManager<AnimationManager>();

    // config manager ready, resize window by config.
    vec2f cameraRectWorldCoordinateSize = GetManager<ConfigManager>()->GetGlobalSetting().cameraRectWorldCoordinateSize;
    float screenWidthHeightRatio = cameraRectWorldCoordinateSize.x / cameraRectWorldCoordinateSize.y;

    uint userDeviceScreenWidth = sf::VideoMode::getDesktopMode().width;
    uint userDeviceScreenHeight = sf::VideoMode::getDesktopMode().height;
    
    float windowWidth = 0.7 * std::min(userDeviceScreenHeight, userDeviceScreenWidth);
    float windowHeight = windowWidth / screenWidthHeightRatio;

    _worldCoordinateToScreenCoordinateScale = windowWidth / cameraRectWorldCoordinateSize.x;

    _pWindow->setSize(vec2u { (uint)windowWidth, (uint)windowHeight });

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
