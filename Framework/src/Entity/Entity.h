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
	// ��std::moveת��uptr������Ȩ
	_compMap[pComp->GetType()] = std::move(pComp);
}

template<typename T>
auto Entity::GetComponent() const -> const T*
{
	// std::unique_ptr��get()�����ڲ�����ָ��
	// Ϊʲô���ﷵ����ָ�룺������������岢�������ߡ�����Ȩ��
	// component������Ȩ������entity�ģ�ֻ�Ƿ���һ��
	// ��˷�����ָ����ⲿ�ü��ɣ��ⲿҲ��Ӧ��delete����Ϊָ��ġ�����Ȩ������
	// �ⲿʹ����ָ����߼�
	auto itr = _compMap.find(T::GetType());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}

template<typename T>
auto Entity::GetComponent() -> T*
{
	// std::unique_ptr��get()�����ڲ�����ָ��
	// Ϊʲô���ﷵ����ָ�룺������������岢�������ߡ�����Ȩ��
	// component������Ȩ������entity�ģ�ֻ�Ƿ���һ��
	// ��˷�����ָ����ⲿ�ü��ɣ��ⲿҲ��Ӧ��delete����Ϊָ��ġ�����Ȩ������
	// �ⲿʹ����ָ����߼�
	auto itr = _compMap.find(T::GetType());
	if (itr == _compMap.end())
		return nullptr;

	auto pBase = itr->second;
	return dynamic_cast<T*>(pBase);
}