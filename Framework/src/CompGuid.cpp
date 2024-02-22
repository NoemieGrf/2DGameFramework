#include "CompGuid.h"

CompGuid::CompGuid(uint runtimeId)
	: _guid(runtimeId)
{
}

CompType CompGuid::GetType() const
{
	return CompType::Guid;
}

uint CompGuid::GetGuid() const
{
	_guid;
}
