#include "UserInputManager.h"
#include "SFML/Window/Keyboard.hpp"
#include "../../Game/Game.h"
#include "../../Entity/Entity.h"
#include "../../Manager/Impl/SceneManager.h"
#include "../../Component/Impl/CompCollider.h"

void UserInputManager::PreTick()
{
    static std::vector<sf::Keyboard::Key> allKeyCodeWeCare = {
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::Space,
    };
    
    _thisFramePressedKey.clear();
    _thisFrameReleasedKey.clear();

    for (auto key : allKeyCodeWeCare)
        CheckKeyCode(key);
}

void UserInputManager::Tick()
{
    SceneManager* pSceneManager = Game::GetManager<SceneManager>();
    Entity* pPlayer = pSceneManager->GetPlayerEntity();
    CompCollider* pPlayerCollider = pPlayer->GetComponent<CompCollider>();

    // move left & right
    if (_pressingKeySet.contains(sf::Keyboard::Key::D))
    {
        auto velocity = pPlayerCollider->GetVelocity();
        velocity.x = 3;
        pPlayerCollider->SetVelocity(velocity);
    }
    else if (_pressingKeySet.contains(sf::Keyboard::Key::A))
    {
        auto velocity = pPlayerCollider->GetVelocity();
        velocity.x = -3;
        pPlayerCollider->SetVelocity(velocity); 
    }

    if (_thisFrameReleasedKey.contains(sf::Keyboard::Key::D)
        || _thisFrameReleasedKey.contains(sf::Keyboard::Key::A))
    {
        auto velocity = pPlayerCollider->GetVelocity();
        if (abs(velocity.y) < 0.0001)   // on ground
        {
            velocity.x = 0;
            pPlayerCollider->SetVelocity(velocity); 
        }
    }

    // jump
    if (_thisFramePressedKey.contains(sf::Keyboard::Key::Space))
    {
        auto velocity = pPlayerCollider->GetVelocity();
        if (abs(velocity.y) < 0.0001)
            pPlayerCollider->ApplyImpulse(vec2f {0, 7});
    }
}

void UserInputManager::CheckKeyCode(sf::Keyboard::Key keyCode)
{
    if (sf::Keyboard::isKeyPressed(keyCode))
    {
        // already pressed in last frame
        if (_pressingKeySet.contains(keyCode))
            return;

        // pressed in this frame
        _thisFramePressedKey.insert(keyCode);
        _pressingKeySet.insert(keyCode);
    }
    else
    {
        // already pressed in last frame
        if (_pressingKeySet.contains(keyCode))
        {
            _thisFrameReleasedKey.insert(keyCode);
            if (_pressingKeySet.contains(keyCode))
                _pressingKeySet.erase(keyCode);
        }
    }
}