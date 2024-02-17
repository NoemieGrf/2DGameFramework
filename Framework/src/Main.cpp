#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Player.h"

using uint = unsigned int;

int main()
{
    // create the window
    uint screenHeight = sf::VideoMode::getDesktopMode().height;
    uint screenWidth = sf::VideoMode::getDesktopMode().width;

    uint minSize = std::min(screenHeight, screenWidth);
    uint windowSize = 0.7 * minSize;

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Test"); 

    // create all renders
    std::vector<IRender*> allRenderVec;

    // create a player
    Player player("./assets/player.png");
    allRenderVec.push_back(&player);

    player.SetSize(50.0f, 50.0f);
    player.SetPosition(sf::Vector2f(100.0f, 100.0f));

    float speed = 500.0f;

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        // Deal time
        sf::Time deltaTime = clock.getElapsedTime();
        clock.restart();
        float deltaTimeSecond = deltaTime.asSeconds();

        // Window event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // User input
        auto [positionX, positionY] = player.GetPosition();
        auto [sizeX, sizeY] = player.GetSize();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && positionY > 0)
        {
            positionY -= speed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && positionY + sizeY < windowSize)
        {
            positionY += speed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && positionX > 0)
        {
            positionX -= speed * deltaTimeSecond;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && positionX + sizeX < windowSize)
        {
            positionX += speed * deltaTimeSecond;
        }

        player.SetPosition(sf::Vector2f(positionX, positionY));

        // Render 
        window.clear(sf::Color::White);
        
        for (IRender* pRender : allRenderVec)
            pRender->Render(window);

        window.display();
    }

    return 0;
}