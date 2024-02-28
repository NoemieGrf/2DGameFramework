#pragma once

#include "Component.h"

template <ComponentType T>
class ComponentTypeGetter : public Component
{
public:
	ComponentType GetType() const override
	{
		return T;
	}

	static ComponentType Type()
	{
		return T;
	}
};