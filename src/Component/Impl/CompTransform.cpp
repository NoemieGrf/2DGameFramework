#include "CompTransform.h"

CompTransform::CompTransform()
	: _position(vec2f(0, 0))
{
}

CompTransform::CompTransform(const vec2f& initPos)
	: _position(initPos)
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
