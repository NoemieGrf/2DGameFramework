#pragma once

class Noncopyable
{
public:
	Noncopyable() = default;
	Noncopyable(const Noncopyable& rhs) = delete;
	Noncopyable& operator= (const Noncopyable& rhs) = delete;
};
