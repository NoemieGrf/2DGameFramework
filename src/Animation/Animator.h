#pragma once

#include <functional>
#include "Condition/AnimTransConditionFactory.h"

class Animator
{
public:


private:
    std::function<void(const std::string& from, const std::string& to)> _onTransition;
    

};