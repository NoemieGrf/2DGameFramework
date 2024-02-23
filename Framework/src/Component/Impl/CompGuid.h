#pragma once

#include "GlobalDefine.h"
#include "ComponentTypeGetter.h"

class CompGuid : public ComponentTypeGetter<CompType::Guid>
{
public:
	explicit CompGuid(uint runtimeId);

public:
	uint GetGuid() const;

private:
	uint _guid;
};