#include "CompSpine.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"
#include "Utility/Util.hpp"
#include "spine/SkeletonData.h"
#include <cstdlib>

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

float CompSpine::GetCurrentAnimProgress() const
{
    auto* pAnimTrack = _pSpine->state->getCurrent(0);
    float animTime = pAnimTrack->getAnimationTime();
    float duration = pAnimTrack->getAnimationEnd() - pAnimTrack->getAnimationStart();
    float result = animTime / duration;
    return Util::Clamp01(result);
}

sf::Drawable* CompSpine::GetSfmlDrawable() const
{
    return _pSpine.get();
}

void CompSpine::SetSfmlDrawableScreenCoordinate(const vec2f& coord)
{
    // ATTENTION!
    // The screen position of spine is quiet special, in spine,
    // the root point is the middle of avatar's feet, so all of 
    // body is drew above the root point. By this reason, the
    // screen position of spine should be original position plus
    // half of height, which will make whole avatar move down
    // half of height.
    vec2f screenSize = GetRenderSizeInScreenCoordinate();
    _pSpine->skeleton->setPosition(coord.x, coord.y + screenSize.y / 2);
}

void CompSpine::SetFlip(bool doFlip)
{
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    float scaleX = pSkeleton->getScaleX();

    if (doFlip)
        scaleX = - abs(scaleX);
    else
        scaleX = abs(scaleX);

    pSkeleton->setScaleX(scaleX);
}
