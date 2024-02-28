#include "CompAi.h"

void CompAi::SetTactic(uptr<Tactic>&& pTactic)
{
    _pTactic = std::move(pTactic);
}

const Tactic* CompAi::GetTactic() const
{
    return _pTactic.get();
}