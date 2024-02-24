#pragma once

#include <random>
#include "../Game/GlobalDefine.h"

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

    inline static bool IsRectOverlap(
        const vec2f& Rect1TopLeft, 
        const vec2f& Rect1DownRight, 
        const vec2f& Rect2TopLeft, 
        const vec2f& Rect2DownRight)
    {
        bool xOverlap = Rect1TopLeft.x <= Rect2DownRight.x && Rect1DownRight.x >= Rect2TopLeft.x;
        bool yOverlap = Rect1TopLeft.y >= Rect2DownRight.y && Rect1DownRight.y <= Rect2TopLeft.y;
    
        return xOverlap && yOverlap;
    }

    inline static bool IsRectContains(
        const vec2f& outerRectTopLeft, 
        const vec2f& outerRectDownRight, 
        const vec2f& innerRectTopLeft, 
        const vec2f& innerRectDownRight)
    {
        return (innerRectTopLeft.x >= outerRectTopLeft.x &&
            innerRectTopLeft.y >= outerRectTopLeft.y &&
            innerRectDownRight.x <= outerRectDownRight.x &&
            innerRectDownRight.y <= outerRectDownRight.y);
    }
};