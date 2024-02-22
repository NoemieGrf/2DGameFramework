#pragma once

#include "GlobalDefine.h"
#include "ComponentType.h"

class Component
{
public:
	// ������Ļ��࣬������������ģ�����������ʱ���޷�ִ�����������
	virtual ~Component() = default;

public:
	virtual CompType GetType() const = 0;
};