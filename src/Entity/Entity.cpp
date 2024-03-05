#include "Entity.h"

#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompName.h"

uint Entity::GetRuntimeId() const
{
	const CompGuid* pCompGuid = GetComponent<CompGuid>();
	if (pCompGuid == nullptr)
		return 0;

	return pCompGuid->GetGuid();
}

const std::string& Entity::GetName() const
{
	return GetComponent<CompName>()->GetName();
}
