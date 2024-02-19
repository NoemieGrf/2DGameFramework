#include "Game.h"

// std
#include <fstream>
#include <iostream>
// 3rd party
#include "SFML/Window.hpp"
#include "nlohmann/json.hpp"
// myself
#include "Player.h"

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

    auto nodePlayerInitPos = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitPosition"];
    _pGameSetting->playerInitPosition.x = nodePlayerInitPos["X"];
    _pGameSetting->playerInitPosition.y = nodePlayerInitPos["Y"];

    auto nodePlayerInitSize = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitSize"];
    _pGameSetting->playerInitSize.x = nodePlayerInitSize["Width"];
    _pGameSetting->playerInitSize.y = nodePlayerInitSize["Height"];

    _pGameSetting->playerInitMoveSpeed = gameConfig["BasicGameSetting"]["PlayerSetting"]["PlayerInitMoveSpeed"];
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
    // create a player
    _pPlayer = std::make_unique<Player>("./assets/player.png");
    // intialise the player
    _pPlayer->SetPosition(_pGameSetting->playerInitPosition);
    _pPlayer->SetSize(_pGameSetting->playerInitSize);
    _pPlayer->SetSpeed(_pGameSetting->playerInitMoveSpeed);
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
        auto [positionX, positionY] = _pPlayer->GetPosition();
        auto [sizeX, sizeY] = _pPlayer->GetSize();
        float playerSpeed = _pPlayer->GetSpeed();
        auto [windowsSizeX, windowSizeY] = _pWindow->getSize();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && positionY - sizeY * 0.5f > 0)
        {
            positionY -= playerSpeed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && positionY + sizeY * 0.5f < windowSizeY)
        {
            positionY += playerSpeed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && positionX - sizeX * 0.5f > 0)
        {
            positionX -= playerSpeed * deltaTimeSecond;
            _pPlayer->SetFlip(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && positionX + sizeX * 0.5f < windowsSizeX)
        {
            positionX += playerSpeed * deltaTimeSecond;
            _pPlayer->SetFlip(true);
        }

        _pPlayer->SetPosition(sf::Vector2f(positionX, positionY));

        // Renderer
        _pWindow->clear(sf::Color::White);
        _pWindow->draw(_pPlayer->GetDrawable());
        _pWindow->display();
    }
}

void Game::Destroy()
{
}
