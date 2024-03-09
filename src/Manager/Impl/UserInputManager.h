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

private:
    auto CheckKeyCode(sf::Keyboard::Key keyCode) -> void;

private:
    uset<sf::Keyboard::Key> _thisFramePressedKey;
    uset<sf::Keyboard::Key> _thisFrameReleasedKey;
    uset<sf::Keyboard::Key> _pressingKeySet;
};