#pragma once

#include "spine-sfml/spine-sfml.h"
#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompSpine : public ComponentTypeGetter<ComponentType::SpineRender>
{
public:
	auto Load(const std::string& spineName) -> void;
    auto GetSkeletonDrawable() -> spine::SkeletonDrawable*;
	auto SetAnimation(const std::string& animName, bool isLoop) -> void;

private:
	uptr<spine::SkeletonDrawable> _pSpine = nullptr;
};