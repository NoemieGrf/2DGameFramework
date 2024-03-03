#include "SpineFactory.h"
#include <memory>
#include "../Game/Game.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Utility/Logger.h"
#include "spine/Atlas.h"
#include "spine/SkeletonJson.h"

uptr<spine::SkeletonDrawable> SpineFactory::CreateSpineDrawable(const std::string& spineName)
{
    auto itr = _spineResourcePool.find(spineName);
    if (itr != _spineResourcePool.end())
    {
        const SpineResData& spineData = itr->second;
        return std::make_unique<spine::SkeletonDrawable>(spineData.pSkeletonData.get());
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

        // 1. create the texture loader
        uptr<spine::SFMLTextureLoader> pTextureLoader = std::make_unique<spine::SFMLTextureLoader>();

        // 2. create the atlas and the use texture loader to load the PNG file.
        uptr<spine::Atlas> pAtlas = std::make_unique<spine::Atlas>(spineSetting.atlasPath.c_str(), pTextureLoader.get());
        if (pAtlas == nullptr)
        {
            Logger::LogError(std::string("Spine load png failed, spine name = ") + spineName);
            return nullptr;
        }

        // 3. create skeleton json and use it to load skeleton data
        spine::SkeletonJson tempSkeletonJson(pAtlas.get());
        tempSkeletonJson.setScale(spineSetting.loadScale);

        spine::SkeletonData* pSkeletonDataRaw = tempSkeletonJson.readSkeletonDataFile(spineSetting.jsonPath.c_str());
        uptr<spine::SkeletonData> pSkeletonData(pSkeletonDataRaw);

        // 4. save all unique ptr
        SpineResData spineData;
        spineData.pTextureLoader = std::move(pTextureLoader);
        spineData.pAtlasData = std::move(pAtlas);
        spineData.pSkeletonData = std::move(pSkeletonData);
        _spineResourcePool[spineName] = std::move(spineData);

        // 5. make SFML drawable and return
        return std::make_unique<spine::SkeletonDrawable>(spineData.pSkeletonData.get());
    }
}