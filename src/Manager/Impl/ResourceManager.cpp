#include "ResourceManager.h"
#include <memory>
#include "../../Game/Game.h"
#include "../../Manager/Impl/ConfigManager.h"
#include "../../Utility/Logger.h"
#include "SFML/Graphics/Texture.hpp"
#include "spine/Atlas.h"
#include "spine/SkeletonJson.h"

uptr<spine::SkeletonDrawable> ResourceManager::CreateSpineDrawable(const std::string& spineName)
{
    uptr<spine::SkeletonDrawable> pResult = nullptr;

    auto itr = _spineResourcePool.find(spineName);
    if (itr != _spineResourcePool.end())
    {
        const SpineResData& spineData = itr->second;
        pResult = std::make_unique<spine::SkeletonDrawable>(spineData.pSkeletonData.get(), spineData.pAnimationMixer.get());
    }
    else
    {
        // 0. get spine json path and atlas path.
        auto gameSpineSetting = Game::GetManager<ConfigManager>()->GetSpineSetting();
        if (!gameSpineSetting.allSpineData.contains(spineName))
        {
            Logger::LogError(std::string("Find spine config failed, spine name = ") + spineName);
            return nullptr;
        }

        auto& spineSetting = gameSpineSetting.allSpineData.at(spineName);

        // 1. create the texture loader.
        uptr<spine::SFMLTextureLoader> pTextureLoader = std::make_unique<spine::SFMLTextureLoader>();

        // 2. create the atlas and the use texture loader to load the PNG file.
        uptr<spine::Atlas> pAtlas = std::make_unique<spine::Atlas>(spineSetting.atlasPath.c_str(), pTextureLoader.get());
        if (pAtlas == nullptr)
        {
            Logger::LogError(std::string("Spine load png failed, spine name = ") + spineName);
            return nullptr;
        }

        // 3. create skeleton json and use it to load skeleton data.
        spine::SkeletonJson tempSkeletonJson(pAtlas.get());
        tempSkeletonJson.setScale(spineSetting.loadScale);

        spine::SkeletonData* pSkeletonDataRaw = tempSkeletonJson.readSkeletonDataFile(spineSetting.jsonPath.c_str());
        uptr<spine::SkeletonData> pSkeletonData(pSkeletonDataRaw);

        // 4. create animation mixer.
        uptr<spine::AnimationStateData> pAnimationMixer = std::make_unique<spine::AnimationStateData>(pSkeletonDataRaw);
        for (const auto& animMixPair: spineSetting.animationData)
            pAnimationMixer->setMix(animMixPair.from.c_str(), animMixPair.to.c_str(), animMixPair.mixTime);

        // 5. save all unique ptr.
        SpineResData& spineResData = _spineResourcePool[spineName];
        spineResData.pTextureLoader = std::move(pTextureLoader);
        spineResData.pAtlasData = std::move(pAtlas);
        spineResData.pSkeletonData = std::move(pSkeletonData);
        spineResData.pAnimationMixer = std::move(pAnimationMixer);

        // 6. make SFML drawable and return.
        pResult = std::make_unique<spine::SkeletonDrawable>(
            spineResData.pSkeletonData.get(), 
            spineResData.pAnimationMixer.get()
            );
    }

    // common setting
    pResult->timeScale = 1;
    pResult->setUsePremultipliedAlpha(true);

    return pResult;
}

uptr<sf::Sprite> ResourceManager::CreateSpriteDrawable(const std::string& pngPath)
{
    auto itr = _textureResourcePool.find(pngPath);
    if (itr == _textureResourcePool.end())
    {
        _textureResourcePool[pngPath].loadFromFile(pngPath);
    }

    uptr<sf::Sprite> pSprite = std::make_unique<sf::Sprite>();

    // set texture to sprite.
    const sf::Texture& texture = _textureResourcePool[pngPath];
    pSprite->setTexture(texture);

    // set original to the center of the texture.
	vec2f textureSize = VecConvert<unsigned int, float>(texture.getSize());
	pSprite->setOrigin(vec2f{ textureSize.x / 2.0f, textureSize.y / 2.0f});

    return pSprite;
}

