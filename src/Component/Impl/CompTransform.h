#pragma once

#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompTransform : public ComponentTypeGetter<CompType::Transform>
{
public:
	CompTransform();
	CompTransform(const vec2f& initPos);

public:
	const vec2f& GetPosition() const;
	void SetPosition(const vec2f& newPosition);

private:
	vec2f _position;
};