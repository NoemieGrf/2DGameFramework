#pragma once

#include "ComponentType.h"
#include "../Utility/Noncopyable.h"

// include Entity.h directly will cause recursive inclusion.
class Entity;

class Component: Noncopyable
{
public:
	virtual ~Component() = default;

public:
	virtual ComponentType GetType() const = 0;

public:
	auto SetEntity(Entity* pEntity) -> void;
	auto GetEntity() const -> Entity*;

private:
	Entity* _pParentEntity = nullptr;
};