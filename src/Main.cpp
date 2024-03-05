
#include "Game/Game.h"

#include "spine-sfml/spine-sfml.h"
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
    // test spine
    const char* jsonPath = "./assets/spine/player/player.json";
    const char* atlasPath = "./assets/spine/player/player.atlas";

    // load altas
    spine::SFMLTextureLoader textureLoader;
    auto pAtlas = new spine::Atlas(atlasPath, &textureLoader);

    // load json
    spine::SkeletonJson json(pAtlas);
    json.setScale(0.2f);
    auto pSkeletonData = json.readSkeletonDataFile(jsonPath);
    if (!pSkeletonData)
    {
        printf("%s\n", json.getError().buffer());
        std::cout << "error" << std::endl;
    }

    spine::AnimationStateData mix(pSkeletonData);
    mix.setMix("Wait1Loop", "Run", 0.1f);
    mix.setMix("Run", "Wait1Loop", 0.1f);
    mix.setMix("Attack", "Wait1Loop", 0.2f);


    spine::SkeletonDrawable drawable(pSkeletonData, &mix);
    drawable.timeScale = 1;
    drawable.setUsePremultipliedAlpha(true);
 
    spine::Skeleton* pSkeleton = drawable.skeleton;
    pSkeleton->setPosition(300, 300);
    pSkeleton->updateWorldTransform();
    pSkeleton->setScaleX(-1);

    drawable.state->setAnimation(0, "Wait1Loop", true);

    sf::RenderWindow window(sf::VideoMode(640, 640), "Spine SFML - example");
    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    bool _lastDPress = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        float delta = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !_lastDPress)
        {
            _lastDPress = true;
            drawable.state->setAnimation(0, "Run", true);
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _lastDPress)
        {
            _lastDPress = false;
            drawable.state->setAnimation(0, "Wait1Loop", true);
        }
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            drawable.state->setAnimation(0, "Attack", false);
            drawable.state->addAnimation(0, "Wait1Loop", true, 1.0f);
        }

        drawable.update(delta);

        window.clear();
        window.draw(drawable);
        window.display();
    }

    /*
    Game::GetInstance()->Init();
    Game::GetInstance()->GameLoop();
    Game::GetInstance()->Destroy();
    */
    return 0;
}