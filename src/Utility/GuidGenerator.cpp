#include "GuidGenerator.h"

using uint = unsigned int;

uint GuidGenerator::GetNextRuntimeId()
{
	uint id = _nextId;
	_nextId++;
	return id;
}

