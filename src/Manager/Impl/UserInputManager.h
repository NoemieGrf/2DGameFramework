#pragma once

#include "../GameManagerTypeGetter.h"
#include "../../Game/GlobalDefine.h"
#include "SFML/Window/Keyboard.hpp"
#include <vector>

class UserInputManager: public GameManagerTypeGetter<GameManagerType::UserInput>
{
public:
    auto PreTick() -> void override;
    auto Tick() -> void override;

public:
    bool IsKeyPressedThisFrame(sf::Keyboard::Key keyCode) const;
    bool IsKeyReleasedThisFrame(sf::Keyboard::Key keyCode) const;
    bool IsKeyPressing(sf::Keyboard::Key keyCode) const;

private:
    auto CheckKeyCode(sf::Keyboard::Key keyCode) -> void;

private:
    uset<sf::Keyboard::Key> _thisFramePressedKey;
    uset<sf::Keyboard::Key> _thisFrameReleasedKey;
    uset<sf::Keyboard::Key> _pressingKeySet;
};