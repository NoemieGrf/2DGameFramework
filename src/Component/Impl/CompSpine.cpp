#include <format>
#include "CompSpine.h"
#include "Game/Game.h"
#include "Entity/Entity.h"
#include "Manager/Impl/ResourceManager.h"
#include "Utility/Util.hpp"
#include "Utility/Logger.h"
#include "spine/SkeletonData.h"

void CompSpine::Load(const std::string& spineName, float widthInWorld, const AnimatorConfig* pAnimatorConfig)
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

    // set animator
    _pAnimatorConfig = pAnimatorConfig;
    SetAnimation("idle");
}

void CompSpine::UpdateSkeletonDrawable(float deltaTime)
{
    _pSpine->update(deltaTime);
}

void CompSpine::SetAnimation(const std::string& animName)
{
    if (_pAnimatorConfig == nullptr)
    {
        Logger::LogError("Comp spine does not have animator config");
        return;
    }

    const auto& nameMap = _pAnimatorConfig->animationConfigMap;
    auto itr = nameMap.find(animName);
    if (itr == nameMap.end())
    {
        Logger::LogError(std::format("Animator config does not have animation named {}", animName));
        return;
    }

    const auto& animationConfig = itr->second;
    _pSpine->state->setAnimation(0, animationConfig.spineName.c_str(), animationConfig.isLoop);
    _currentAnim = animName;
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

void CompSpine::EnqueueAnimTrigger(const std::string& trigger)
{
    _animTriggers.push(trigger);
}

std::optional<std::string> CompSpine::DequeueAnimTrigger()
{
    if (_animTriggers.empty())
        return std::nullopt;

    std::string result = _animTriggers.front();
    _animTriggers.pop();
    return result;
}

void CompSpine::UpdateAnimator()
{
    if (_pAnimatorConfig == nullptr)
    {
        Logger::LogError("Comp spine does not have animator config");
        return;
    }

    const auto& nameMap = _pAnimatorConfig->animationConfigMap;
    auto itr = nameMap.find(_currentAnim);
    if (itr == nameMap.end())
        return;

    const auto& transitions = (itr->second).transitions;
    Entity* pParentEntity = GetEntity();
    for (const auto& [nextAnimName, conditionVec]: transitions)
    {
        bool canTransToNextAnim = true;
        for (const auto& pCondition: conditionVec)
        {
            canTransToNextAnim &= pCondition->Check(pParentEntity);
            if (!canTransToNextAnim)
                break;
        }

        if (canTransToNextAnim)
        {
            SetAnimation(nextAnimName);
            break;
        }
    }
}
