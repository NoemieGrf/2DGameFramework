#pragma once

#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompTransform : public ComponentTypeGetter<ComponentType::Transform>
{
public:
	CompTransform();
	CompTransform(const vec2f& initPos);

public:
	auto GetPosition() const -> const vec2f&;
	auto SetPosition(const vec2f& newPosition) -> void;

private:
	vec2f _position;
};