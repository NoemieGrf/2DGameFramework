#pragma once

#include "../../AI/Tactic.h"
#include "../ComponentTypeGetter.h"

class CompAi : public ComponentTypeGetter<ComponentType::Ai>
{
public:
    auto SetTactic(uptr<Tactic>&& pTactic) -> void;
    auto GetTactic() const -> const Tactic*;

private:
    uptr<Tactic> _pTactic = nullptr;
};