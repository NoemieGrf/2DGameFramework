#include "Animator.h"

Animator::Animator(const AnimatorConfig* transitionMap, const OnAnimationChanged& onAnimChanged)
    : _animationTransitionMap(transitionMap)
    , _onAnimChanged(onAnimChanged)
{
}

void Animator::Update()
{
    if (_animationTransitionMap == nullptr)
        return;

    const auto& animTransMap = _animationTransitionMap->transitions;
    auto itr = animTransMap.find(_currentAnimation);
    if (itr  == animTransMap.end())
        return;

    const auto& allPossibleNextAnimVec = itr->second;

}