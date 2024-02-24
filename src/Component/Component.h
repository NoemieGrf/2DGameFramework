#pragma once

#include "ComponentType.h"

class Component
{
public:
	// 有子类的基类，析构必须是虚的，否则析构的时候无法执行子类的析构
	virtual ~Component() = default;

public:
	virtual CompType GetType() const = 0;
};