#include "Game.h"

// std
#include <memory>
// 3rd party
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


Game::Game() = default;

void Game::Init()
{
    // create camera
    _pMainCamera = std::make_unique<Camera>();

    // create game manager, order is really important!
    AddManager<ConfigManager>();
    AddManager<ResourceManager>();
    AddManager<UserInputManager>();
    AddManager<PhysicsManager>();
    AddManager<AnimationManager>();
    AddManager<SceneManager>();
    AddManager<AiManager>();

    // init window
    vec2f cameraRectWorldCoordinateSize = GetManager<ConfigManager>()->GetGlobalSetting().cameraRectWorldCoordinateSize;
    float screenWidthHeightRatio = cameraRectWorldCoordinateSize.x / cameraRectWorldCoordinateSize.y;

    uint userDeviceScreenWidth = sf::VideoMode::getDesktopMode().width;
    uint userDeviceScreenHeight = sf::VideoMode::getDesktopMode().height;
    
    float windowWidth = 0.9 * std::min(userDeviceScreenHeight, userDeviceScreenWidth);
    float windowHeight = windowWidth / screenWidthHeightRatio;

    _worldCoordinateToScreenCoordinateScale = windowWidth / cameraRectWorldCoordinateSize.x;

    _pWindow = std::make_unique<sf::RenderWindow>(
        sf::VideoMode((uint)windowWidth, (uint)windowHeight), 
        "2DGame",
        sf::Style::Titlebar | sf::Style::Close  // no resize
        );

    _pWindow->setFramerateLimit(60);

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
        _pWindow->clear(sf::Color{220, 220, 220});
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

float Game::GetWorldCoordinateToScreenCoordinateScale()
{
    return GetInstance()->_worldCoordinateToScreenCoordinateScale;
}

Camera* Game::GetCamera()
{
    return GetInstance()->_pMainCamera.get();
}

float Game::GetDeltaTime()
{
    return GetInstance()->_deltaTimeSecond;
}
