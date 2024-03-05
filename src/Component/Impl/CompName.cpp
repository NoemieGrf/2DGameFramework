#include "CompName.h"

void CompName::SetName(const std::string& newName)
{
    _name = newName;
}

const std::string& CompName::GetName() const
{
    return _name;
}