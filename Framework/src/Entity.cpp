#include "Entity.h"

void Entity::AddComponent(uptr<Component>&& pComp)
{
	// 用std::move转移uptr的所有权
	_compMap[pComp->GetType()] = std::move(pComp);
}

Component* Entity::GetComponent(CompType t)
{
	// std::unique_ptr的get()返回内部的裸指针
	// 为什么这里返回裸指针：这个函数的语义并不是拿走“所有权”
	// component的所有权还是在entity的，只是访问一下
	// 因此返回裸指针给外部用即可（外部也不应当delete，因为指针的“所有权”不是
	// 外部使用裸指针的逻辑
	if (_compMap.contains(t))
		return _compMap[t].get();

	return nullptr;
}

