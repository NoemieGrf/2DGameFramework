#pragma once

#include <vector>
#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "spine-sfml/spine-sfml.h"
#include "../GameManagerTypeGetter.h"
#include "../../Game/GlobalDefine.h"
#include "spine/AnimationStateData.h"

class ResourceManager: public GameManagerTypeGetter<GameManagerType::Resource>
{
public:
    auto CreateSpineDrawable(const std::string& spineName) -> uptr<spine::SkeletonDrawable>;
    auto CreateSpriteDrawable(const std::string& pngPath) -> uptr<sf::Sprite>;

private:
    struct SpineResData
    {
        // texture loader -> hold the real data of PNG file.
        uptr<spine::SFMLTextureLoader> pTextureLoader = nullptr;

        // atlas -> hold the reference of real PNG file, and all slices of PNG.
        uptr<spine::Atlas> pAtlasData = nullptr;

        // skeleton -> hold the real data of skeleton data & reference to atlas.
        uptr<spine::SkeletonData> pSkeletonData = nullptr;

        // animation -> hold the data of animation blend.
        uptr<spine::AnimationStateData> pAnimationMixer = nullptr;
    };

public:
    umap<std::string, SpineResData> _spineResourcePool {};
    umap<std::string, sf::Texture> _textureResourcePool {};
};