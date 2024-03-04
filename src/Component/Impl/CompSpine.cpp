#include "CompSpine.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"
#include "../../Manager/Impl/ConfigManager.h"

void CompSpine::Load(const std::string& spineName)
{
    ResourceManager* resMgr = Game::GetManager<ResourceManager>();
    ConfigManager* configMgr = Game::GetManager<ConfigManager>();

    _pSpine = resMgr->CreateSpineDrawable(spineName);

    // set some default value
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    pSkeleton->setPosition(0, 0); 
    pSkeleton->updateWorldTransform();

    // calculate screen size
    float spineImportScale = 1;
    auto allSpineConfig = configMgr->GetSpineSetting().allSpineData;
    auto itr = allSpineConfig.find(spineName);
    if (itr != allSpineConfig.end())
        spineImportScale = (itr->second).loadScale;

    spine::SkeletonData* pSkeletonData = pSkeleton->getData();
    float widthInSpine = pSkeletonData->getWidth();
    float heightInSpine = pSkeletonData->getHeight();
    _screenSize = vec2f {
        widthInSpine * spineImportScale,
        heightInSpine * spineImportScale
    };
}

spine::SkeletonDrawable* CompSpine::GetSkeletonDrawable()
{
    return _pSpine.get();
}

void CompSpine::SetAnimation(const std::string& animName, bool isLoop)
{
    _pSpine->state->setAnimation(0, animName.c_str(), isLoop);
}

vec2f CompSpine::GetRenderSizeInScreenCoordinate()
{
    float scaleX = _pSpine->skeleton->getScaleX();
    float scaleY = _pSpine->skeleton->getScaleY();

    return vec2f { 
        _screenSize.x * abs(scaleX), 
        _screenSize.y * abs(scaleY) 
        };
}
