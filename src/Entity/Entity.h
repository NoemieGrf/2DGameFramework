#pragma once

#include "../Game/GlobalDefine.h"
#include "../Component/ComponentType.h"
#include "../Component/Component.h"

class Entity
{
public:
	Entity() = default;

public:

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
	_compMap[pComp->GetType()] = std::move(pComp);
}

template<typename T>
auto Entity::GetComponent() const -> const T*
{
	auto itr = _compMap.find(T::Type());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}

template<typename T>
auto Entity::GetComponent() -> T*
{

	auto itr = _compMap.find(T::Type());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}