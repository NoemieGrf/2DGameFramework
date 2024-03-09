#include "CompSpine.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"
#include "spine/SkeletonData.h"

void CompSpine::Load(const std::string& spineName, float widthInWorld)
{
    ResourceManager* resMgr = Game::GetManager<ResourceManager>();

    _pSpine = resMgr->CreateSpineDrawable(spineName);

    float scaleFromWorldToScreen = Game::GetWorldCoordinateToScreenCoordinateScale();
    float widthInScreen = scaleFromWorldToScreen * widthInWorld;

    // set some default value
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    pSkeleton->setPosition(0, 0); 
    pSkeleton->updateWorldTransform();

    // calculate screen size
    spine::SkeletonData* pSkeletonData = pSkeleton->getData();
    auto originalWidth = pSkeletonData->getWidth();
    auto scale = widthInScreen / originalWidth;

    pSkeleton->setScaleX(scale);
    pSkeleton->setScaleY(scale);
}

void CompSpine::UpdateSkeletonDrawable(float deltaTime)
{
    _pSpine->update(deltaTime);
}

float CompSpine::GetSkeletonWidthHeightScale()
{
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    spine::SkeletonData* pSkeletonData = pSkeleton->getData();
    return pSkeletonData->getWidth() / pSkeletonData->getHeight();
}

void CompSpine::SetAnimation(const std::string& animName, bool isLoop)
{
    _pSpine->state->setAnimation(0, animName.c_str(), isLoop);
}

vec2f CompSpine::GetRenderSizeInScreenCoordinate() const
{
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    float scaleX = pSkeleton->getScaleX();
    float scaleY = pSkeleton->getScaleY();

    spine::SkeletonData* pSkeletonData = pSkeleton->getData();
    auto originalWidth = pSkeletonData->getWidth();
    auto originalHeight = pSkeletonData->getHeight();

    return vec2f { 
        originalWidth * abs(scaleX), 
        originalHeight * abs(scaleY) 
        };
}

sf::Drawable* CompSpine::GetSfmlDrawable() const
{
    return _pSpine.get();
}

void CompSpine::SetSfmlDrawableScreenCoordinate(const vec2f& coord)
{
    _pSpine->skeleton->setPosition(coord.x, coord.y);
}
