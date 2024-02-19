#pragma once

class RuntimeIdManager
{
	using uint = unsigned int;

public:
	RuntimeIdManager() = delete;

public:
	static uint GetNextRuntimeId();

private:
	inline static uint _nextId = 0;
};