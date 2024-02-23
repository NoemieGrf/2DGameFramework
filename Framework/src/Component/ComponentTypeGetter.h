#pragma once

#include "Component.h"

template <CompType T>
class ComponentTypeGetter : public Component
{
public:
	CompType GetType() const override
	{
		return T;
	}

	static CompType GetType()
	{
		return T;
	}
};