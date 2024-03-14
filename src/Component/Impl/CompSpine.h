#pragma once

#include "spine-sfml/spine-sfml.h"
#include "CompRender.h"

class CompSpine : public CompRender
{
public:
	auto Load(const std::string& spineName, float widthInWorld) -> void;
	auto SetAnimation(const std::string& animName, bool isLoop) -> void;
	auto UpdateSkeletonDrawable(float deltaTime) -> void;

public:
	auto GetRenderSizeInScreenCoordinate() const -> vec2f override;
	auto GetSfmlDrawable() const -> sf::Drawable* override;
	auto GetCurrentAnimProgress() const -> float;
	auto SetSfmlDrawableScreenCoordinate(const vec2f& coord) -> void override;
	auto SetFlip(bool doFlip) -> void override;

private:
	uptr<spine::SkeletonDrawable> _pSpine = nullptr;
};