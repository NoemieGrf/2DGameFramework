#pragma once

#include <string>
#include "../ComponentTypeGetter.h"

class CompName : public ComponentTypeGetter<ComponentType::Name>
{
public:
    auto SetName(const std::string& newName) -> void;
    auto GetName() const -> const std::string&;

private:
    std::string _name;
};