#include "CompGuid.h"

CompGuid::CompGuid(uint runtimeId)
	: _guid(runtimeId)
{
}

uint CompGuid::GetGuid() const
{
	_guid;
}
