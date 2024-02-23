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
	template<typename T>
	auto AddComponent(uptr<T>&& pComp) -> void;

	template<typename T>
	auto GetComponent() const -> const T*;

	template<typename T>
	auto GetComponent() -> T*;

public:
	auto GetRuntimeId() const -> uint;


private:
	umap<CompType, uptr<Component>> _compMap = {};

};

template<typename T>
auto Entity::AddComponent(uptr<T>&& pComp) -> void
{
	// 用std::move转移uptr的所有权
	_compMap[pComp->GetType()] = std::move(pComp);
}

template<typename T>
auto Entity::GetComponent() const -> const T*
{
	// std::unique_ptr的get()返回内部的裸指针
	// 为什么这里返回裸指针：这个函数的语义并不是拿走“所有权”
	// component的所有权还是在entity的，只是访问一下
	// 因此返回裸指针给外部用即可（外部也不应当delete，因为指针的“所有权”不是
	// 外部使用裸指针的逻辑
	auto itr = _compMap.find(T::GetType());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}

template<typename T>
auto Entity::GetComponent() -> T*
{
	// std::unique_ptr的get()返回内部的裸指针
	// 为什么这里返回裸指针：这个函数的语义并不是拿走“所有权”
	// component的所有权还是在entity的，只是访问一下
	// 因此返回裸指针给外部用即可（外部也不应当delete，因为指针的“所有权”不是
	// 外部使用裸指针的逻辑
	auto itr = _compMap.find(T::GetType());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}