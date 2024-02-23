#include "CompTransform.h"

CompTransform::CompTransform()
	: _position(vec2f(0, 0))
	, _scale(vec2f(1, 1))
{
}

CompTransform::CompTransform(const vec2f& initPos, const vec2f& initScale)
	: _position(initPos)
	, _scale(initScale)
{
}

const vec2f& CompTransform::GetPosition() const
{
	return _position;
}

void CompTransform::SetPosition(const vec2f& newPosition)
{
	_position = newPosition;
}

const vec2f& CompTransform::GetScale() const
{
	return _scale;
}

void CompTransform::SetScale(const vec2f& newScale)
{
	_scale = newScale;
}
