#include "Entity.h"

#include "CompGuid.h"

uint Entity::GetRuntimeId() const
{
	const CompGuid* pCompGuid = GetComponent<CompGuid>();
	if (pCompGuid == nullptr)
		return 0;

	return pCompGuid->GetGuid();
}
