#pragma once

class GuidGenerator
{
	using uint = unsigned int;

public:
	GuidGenerator() = delete;

public:
	static uint GetNextRuntimeId();

private:
	inline static uint _nextId = 0;
};