#pragma once

#include <string>
#include "../Game/GlobalDefine.h"
#include "../Component/ComponentType.h"
#include "../Component/Component.h"

class Entity
{
public:
	Entity() = default;

public:
	template<typename T>
	auto AddComponent() -> T*;

	template<typename T>
	auto GetComponent() const -> const T*;

	template<typename T>
	auto GetComponent() -> T*;

public:	// fast access
	auto GetRuntimeId() const -> uint;
	auto GetName() const -> const std::string&;

private:
	umap<ComponentType, uptr<Component>> _compMap = {};
};

template<typename T>
auto Entity::AddComponent() -> T*
{
	ComponentType t = T::Type();

	uptr<T> pComp = std::make_unique<T>();
	pComp->SetEntity(this);

	T* rawPointer = pComp.get();
	_compMap[t] = std::move(pComp);

	return rawPointer;
}

template<typename T>
auto Entity::GetComponent() const -> const T*
{
	auto itr = _compMap.find(T::Type());
	if (itr == _compMap.end())
		return nullptr;

	return dynamic_cast<T*>(itr->second.get());
}

template<typename T>
auto Entity::GetComponent() -> T*
{
	auto itr = _compMap.find(T::Type());
	if (itr == _compMap.end())
		return nullptr;

	return dynamic_cast<T*>(itr->second.get());
}