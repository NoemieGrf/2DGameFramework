#include <SFML/Graphics.hpp>
#include <algorithm>

using uint = unsigned int;

int main()
{
    uint screenHeight = sf::VideoMode::getDesktopMode().height;
    uint screenWidth = sf::VideoMode::getDesktopMode().width;

    uint minSize = std::min(screenHeight, screenWidth);
    uint windowSize = 0.7 * minSize;

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Test");
    
    sf::Texture tex;
    tex.loadFromFile("./assets/player.png");

    sf::Sprite sp(tex);
    sp.setScale(0.5f, 0.5f);
    
    float spPosX = 100;
    float spPosY = 100;
    
    

    while (window.isOpen())
    {
        // Window event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // User input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            spPosY -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            spPosY += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            spPosX -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            spPosX += 0.1f;
        }




        sp.setPosition(spPosX, spPosY);



        // Render 
        window.clear(sf::Color::White);
        window.draw(sp);
        window.display();
    }

    return 0;
}