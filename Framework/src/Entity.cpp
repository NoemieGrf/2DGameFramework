#include "Entity.h"

void Entity::AddComponent(uptr<Component>&& pComp)
{
	// ��std::moveת��uptr������Ȩ
	_compMap[pComp->GetType()] = std::move(pComp);
}

Component* Entity::GetComponent(CompType t)
{
	// std::unique_ptr��get()�����ڲ�����ָ��
	// Ϊʲô���ﷵ����ָ�룺������������岢�������ߡ�����Ȩ��
	// component������Ȩ������entity�ģ�ֻ�Ƿ���һ��
	// ��˷�����ָ����ⲿ�ü��ɣ��ⲿҲ��Ӧ��delete����Ϊָ��ġ�����Ȩ������
	// �ⲿʹ����ָ����߼�
	if (_compMap.contains(t))
		return _compMap[t].get();

	return nullptr;
}

