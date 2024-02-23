#include "Game.h"

// std
#include <fstream>
#include <iostream>
// 3rd party
#include "SFML/Window.hpp"
#include "nlohmann/json.hpp"
// myself
#include "Player.h"
#include "RuntimeIdManager.h"
#include "Util.hpp"
#include "EntityFactory.h"

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
    // create the player
    _playerEntity = EntityFactory::CreatePlayer();


    // create the player
    _pPlayer = std::make_unique<Player>("./assets/player.png");
    // initialise the player
    _pPlayer->SetPosition(_pGameSetting->playerInitPosition);
    _pPlayer->SetSize(_pGameSetting->playerInitSize);
    _pPlayer->SetSpeed(_pGameSetting->playerInitMoveSpeed);

    // create 3 monsters
    for (int i = 0; i < 3; i++)
    {
        //  create a monster 
        uint id = RuntimeIdManager::GetNextRuntimeId();
        _pMonsters[id] = std::make_unique<Monster>("./assets/monster0.png", id);
        // initialise a monster
        sf::Vector2f originPos = _pGameSetting->monsterInitPosition;
        sf::Vector2 finalPos = originPos + sf::Vector2f(
            Util::GetRandomNumber<float>(10.0f, 300.0f),
            Util::GetRandomNumber<float>(10.0f, 300.0f)
        );
        _pMonsters[id]->SetPosition(finalPos);
        _pMonsters[id]->SetSize(_pGameSetting->monsterInitSize);
        _pMonsters[id]->SetSpeed(_pGameSetting->monsterInitMoveSpeed);
    }
}

void Game::Run()
{
    sf::Clock clock;
    clock.restart();

    while (_pWindow->isOpen())
    {
        // Deal time
        sf::Time deltaTime = clock.getElapsedTime();
        clock.restart();
        float deltaTimeSecond = deltaTime.asSeconds();

        // Window event
        sf::Event event;
        while (_pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _pWindow->close();
        }

        // User input
        // the player status
        auto [windowsSizeX, windowSizeY] = _pWindow->getSize();
        auto [playerPositionX, playerPositionY] = _pPlayer->GetPosition();
        auto [playerSizeX, playerSizeY] = _pPlayer->GetSize();
        float playerSpeed = _pPlayer->GetSpeed();
        // monsters act
        for (auto& [id, pMonster] : _pMonsters)
        {
            auto [monsterPositionX, monsterPositionY] = pMonster->GetPosition();
            float monsterSpeed = pMonster->GetSpeed();

            if (monsterPositionX != playerPositionX)
            {
                float deltaDistanceX = (playerPositionX - monsterPositionX) / abs(playerPositionX - monsterPositionX) * monsterSpeed * deltaTimeSecond;
                monsterPositionX += deltaDistanceX;

                if (abs(playerPositionX - monsterPositionX) > 0.5)
                    pMonster->SetFlip(deltaDistanceX > 0);
            }
            if (monsterPositionY != playerPositionY)
            {
                float deltaDistanceY = (playerPositionY - monsterPositionY) / abs(playerPositionY - monsterPositionY) * monsterSpeed * deltaTimeSecond;
                monsterPositionY += deltaDistanceY;
            }

            pMonster->SetPosition(sf::Vector2f(monsterPositionX, monsterPositionY));
        }

        // the player act
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && playerPositionY - playerSizeY * 0.5f > 0)
        {
            playerPositionY -= playerSpeed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && playerPositionY + playerSizeY * 0.5f < windowSizeY)
        {
            playerPositionY += playerSpeed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && playerPositionX - playerSizeX * 0.5f > 0)
        {
            playerPositionX -= playerSpeed * deltaTimeSecond;
            _pPlayer->SetFlip(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && playerPositionX + playerSizeX * 0.5f < windowsSizeX)
        {
            playerPositionX += playerSpeed * deltaTimeSecond;
            _pPlayer->SetFlip(true);
        }

        _pPlayer->SetPosition(sf::Vector2f(playerPositionX, playerPositionY));
         
        // Renderer
        _pWindow->clear(sf::Color::White);
        _pWindow->draw(_pPlayer->GetDrawable());
        for (auto& [id, pMonster] : _pMonsters)
        {
            _pWindow->draw(pMonster->GetDrawable());
        }
        _pWindow->display();
    }
}

void Game::Destroy()
{
}
