#include "CompGuid.h"

void CompGuid::SetGuid(uint guid)
{
	_guid = guid;
}

uint CompGuid::GetGuid() const
{
	return _guid;
}
