#include "Game.h"

// std
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
// 3rd party
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "nlohmann/json.hpp"
// myself
#include "../Entity/EntityFactory.h"
#include "../Component/Impl/CompTransform.h"
#include "../Component/Impl/CompAi.h"
#include "../Utility/Util.hpp"

Game::Game() = default;

Game* Game::GetInstance()
{
    static Game* pGame = new Game();
    return pGame;
}

void Game::InitConfig()
{
	_pGameSetting = std::make_unique<GameSetting>();

    nlohmann::json gameConfig;
    std::ifstream configJsonFile("./config/GameConfig.json");
    if (!configJsonFile.is_open())
    {
        std::cout << "file fucked\n";
    }

    configJsonFile >> gameConfig;
    configJsonFile.close();

    // player
    auto nodePlayerInitPos = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitPosition"];
    _pGameSetting->playerInitPosition.x = nodePlayerInitPos["X"];
    _pGameSetting->playerInitPosition.y = nodePlayerInitPos["Y"];

    auto nodePlayerInitSize = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitSize"];
    _pGameSetting->playerInitSize.x = nodePlayerInitSize["Width"];
    _pGameSetting->playerInitSize.y = nodePlayerInitSize["Height"];

    _pGameSetting->playerInitMoveSpeed = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitMoveSpeed"];

    // monster
    auto nodeMonsterInitPos = gameConfig["BasicGameSetting"]["MonsterSetting"]["MonsterInitPosition"];
    _pGameSetting->monsterInitPosition.x = nodeMonsterInitPos["X"];
    _pGameSetting->monsterInitPosition.y = nodeMonsterInitPos["Y"];

    auto nodeMonsterInitSize = gameConfig["BasicGameSetting"]["MonsterSetting"]["MonsterInitSize"];
    _pGameSetting->monsterInitSize.x = nodeMonsterInitSize["Width"];
    _pGameSetting->monsterInitSize.y = nodeMonsterInitSize["Height"];

    _pGameSetting->monsterInitMoveSpeed = gameConfig["BasicGameSetting"]["MonsterSetting"]["MonsterInitMoveSpeed"];

}

void Game::InitWindow()
{
    using uint = unsigned int;
    uint screenHeight = sf::VideoMode::getDesktopMode().height;
    uint screenWidth = sf::VideoMode::getDesktopMode().width;
    uint windowSize = 0.7 * std::min(screenHeight, screenWidth);

    _pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize, windowSize), "Test");
}

void Game::InitScene()
{
    // create the camera
    _pMainCamera = std::make_unique<Camera>();

    // create the player
    _playerEntity = EntityFactory::CreatePlayer();
    _allEntitiesMap[_playerEntity->GetRuntimeId()] = _playerEntity;
    
    auto pPlayerTrans = _playerEntity->GetComponent<CompTransform>();
    if (pPlayerTrans != nullptr)
        pPlayerTrans->SetPosition(vec2f{ 0.0f, 0.0f });

    // create the monster
    for (int i = 0; i < 3; i++)
    {
        auto pMonster = EntityFactory::CreateMonster();
        _allEntitiesMap[pMonster->GetRuntimeId()] = pMonster;
        
        auto pMonsterTrans = pMonster->GetComponent<CompTransform>();
        if (pMonsterTrans != nullptr)
        {
            pMonsterTrans->SetPosition(vec2f{ 
                Util::GetRandomNumber<float>(100, 1000), 
                Util::GetRandomNumber<float>(100, 1000) });
        }
    }
}

void Game::Run()
{
    _clock.restart();

    while (_pWindow->isOpen())
    {
        UpdateTime();
        UpdateWindowEvent();
        UpdateUserInput();
        UpdateAI();
        UpdatePhysics();

        RenderScene();
    }
}

void Game::UpdateTime()
{
    sf::Time deltaTime = _clock.getElapsedTime();
    _clock.restart();
    _deltaTimeSecond = deltaTime.asSeconds();
}

void Game::UpdateWindowEvent()
{
    sf::Event event;
    while (_pWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _pWindow->close();
    }
}

void Game::UpdateUserInput()
{

}

void Game::UpdateAI()
{
    for (auto& [id, pEntity]: _allEntitiesMap)
    {
        auto pCompTrans = pEntity->GetComponent<CompTransform>();
        if (pCompTrans == nullptr)
            continue;

        auto pCompAi = pEntity->GetComponent<CompAi>();
        if (pCompAi == nullptr)
            continue;

        auto newPos = pCompAi->GetTactic()->UpdatePosition(pCompTrans->GetPosition());
        pCompTrans->SetPosition(newPos);
    }
}

void Game::UpdatePhysics()
{

}

void Game::RenderScene()
{
    _pWindow->clear(sf::Color::White);
    _pMainCamera->DoRender();
    _pWindow->display();
}

void Game::Destroy()
{
}

sf::RenderWindow* Game::GetWindow() const
{
    return _pWindow.get();
}

Entity* Game::GetPlayerEntity() const
{
    return _playerEntity.get();
}

float Game::GetDeltaTime() const
{
    return _deltaTimeSecond;
}

Camera* Game::GetCamera() const
{
    return _pMainCamera.get();
}

const umap<uint, sptr<Entity>>& Game::GetAllEntities() const
{
    return _allEntitiesMap;
}
