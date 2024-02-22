#pragma once

#include "GlobalDefine.h"
#include "ComponentType.h"
#include "Component.h"

class Entity
{
public:
	Entity() = default;

public:

	// 这里第二个参数是uptr的右值引用，uptr不能赋值，这里右值引用表示“所有权”的转移
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