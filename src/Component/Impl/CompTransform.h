#pragma once

#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompTransform : public ComponentTypeGetter<CompType::Transform>
{
public:
	CompTransform();
	CompTransform(const vec2f& initPos, const vec2f& initScale);

public:
	const vec2f& GetPosition() const;
	void SetPosition(const vec2f& newPosition);

	const vec2f& GetScale() const;
	void SetScale(const vec2f& newScale);

private:
	vec2f _position;
	vec2f _scale;
};