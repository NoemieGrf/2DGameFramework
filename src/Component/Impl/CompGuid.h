#pragma once

#include "../../Game/GlobalDefine.h"
#include "../ComponentTypeGetter.h"

class CompGuid : public ComponentTypeGetter<ComponentType::Guid>
{
public:
	void SetGuid(uint guid);
	uint GetGuid() const;

private:
	uint _guid;
};