#pragma once

#include "spine-sfml/spine-sfml.h"
#include "CompRender.h"

class CompSpine : public CompRender
{
public:
	auto Load(const std::string& spineName) -> void;
    auto GetSkeletonDrawable() -> spine::SkeletonDrawable*;
	auto SetAnimation(const std::string& animName, bool isLoop) -> void;

public:
	auto GetRenderSizeInScreenCoordinate() const -> vec2f override;
	auto GetSfmlDrawable() const -> sf::Drawable* override;
	auto SetSfmlDrawableScreenCoordinate(const vec2f& coord) -> void override;

private:
	uptr<spine::SkeletonDrawable> _pSpine = nullptr;
	vec2f _screenSize;
};