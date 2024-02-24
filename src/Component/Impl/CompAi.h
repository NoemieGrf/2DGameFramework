#pragma once

#include "../../AI/Tactic.h"
#include "../ComponentTypeGetter.h"

class CompAi : public ComponentTypeGetter<CompType::Ai>
{
public:
    CompAi(uptr<Tactic>&& pTactic);

public:
    const Tactic* GetTactic() const;

private:
    uptr<Tactic> _pTactic = nullptr;
};