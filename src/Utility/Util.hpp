#pragma once

#include <random>

class Util
{
public:
	Util() = delete;

public:
	template<typename T>
	static T GetRandomNumber(T inferiority, T superiority)
	{
        std::random_device rd;
        std::mt19937 gen(rd());
        if constexpr (std::is_integral<T>::value) 
        { 
            std::uniform_int_distribution<T> dis(inferiority, superiority);
            return dis(gen);
        }
        else if constexpr (std::is_floating_point<T>::value) 
        {
            std::uniform_real_distribution<T> dis(inferiority, superiority);
            return dis(gen);
        }
        else 
        {
            throw std::invalid_argument("Unsupported type!");
        }
	}
};