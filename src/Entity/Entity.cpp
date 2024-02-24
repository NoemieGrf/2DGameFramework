#include "Entity.h"

#include "../Component/Impl/CompGuid.h"

uint Entity::GetRuntimeId() const
{
	const CompGuid* pCompGuid = GetComponent<CompGuid>();
	if (pCompGuid == nullptr)
		return 0;

	return pCompGuid->GetGuid();
}
