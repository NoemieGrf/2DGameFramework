#include "Component.h"
#include "../Entity/Entity.h"

void Component::SetEntity(Entity* pEntity)
{
    _pParentEntity = pEntity;
}

Entity* Component::GetEntity() const 
{
    return _pParentEntity;
}
