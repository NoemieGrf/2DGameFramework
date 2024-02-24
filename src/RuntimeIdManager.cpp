#include "RuntimeIdManager.h"

using uint = unsigned int;

uint RuntimeIdManager::GetNextRuntimeId()
{
	uint id = _nextId;
	_nextId++;
	return id;
}

