#pragma once

#include "GlobalDefine.h"
#include "ComponentType.h"
#include "Component.h"

class Entity
{
public:
	Entity() = default;

public:

	// ����ڶ���������uptr����ֵ���ã�uptr���ܸ�ֵ��������ֵ���ñ�ʾ������Ȩ����ת��
	auto AddComponent(uptr<Component>&& pComp) -> void;
	auto GetComponent(CompType t) -> Component*;

	template<typename T>
	auto GetComponent(CompType t) -> T*;

public:
	auto GetRuntimeId() const -> uint;


private:
	umap<CompType, uptr<Component>> _compMap = {};

};

template<typename T>
auto GetComponent(CompType t) -> T*
{

}