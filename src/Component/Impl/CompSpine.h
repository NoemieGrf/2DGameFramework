#pragma once

#include <queue>
#include <string>
#include <optional>
#include "spine-sfml/spine-sfml.h"
#include "CompRender.h"
#include "Config/AnimationSetting.h"

class CompSpine : public CompRender
{
public:
	auto Load(const std::string& spineName, float widthInWorld, const AnimatorConfig* pAnimatorConfig) -> void;
	
	// render
	auto GetRenderSizeInScreenCoordinate() const -> vec2f override;
	auto GetSfmlDrawable() const -> sf::Drawable* override;
	auto GetCurrentAnimProgress() const -> float;
	auto SetSfmlDrawableScreenCoordinate(const vec2f& coord) -> void override;
	auto SetFlip(bool doFlip) -> void override;

	// animation
    auto EnqueueAnimTrigger(const std::string& trigger) -> void;
    auto DequeueAnimTrigger() -> std::optional<std::string>;

	// update
	auto UpdateAnimator() -> void;
	auto UpdateSkeletonDrawable(float deltaTime) -> void;

private:
	auto SetAnimation(const std::string& animName) -> void;

private:
	// render
	uptr<spine::SkeletonDrawable> _pSpine = nullptr;

	// animator config
    const AnimatorConfig* _pAnimatorConfig;

	// animator current
	std::string _currentAnim;

	// animator triggers
    std::queue<std::string> _animTriggers;
};