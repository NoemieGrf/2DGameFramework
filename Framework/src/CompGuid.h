#pragma once

#include "GlobalDefine.h"
#include "Component.h"

class CompGuid : public Component
{
public:
	explicit CompGuid(uint runtimeId);

public: // override
	CompType GetType() const override;

public:
	uint GetGuid() const;

private:
	uint _guid
};