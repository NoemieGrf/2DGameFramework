#include "CompAnimator.h"
#include "CompSpine.h"
#include "CompCollider.h"
#include "../../Utility/Util.hpp"
#include "../../Entity/Entity.h"

void CompAnimator::Update()
{
    CompSpine* pSpine = GetEntity()->GetComponent<CompSpine>();
    if (pSpine == nullptr)
        return;

    CompCollider* pCollider = GetEntity()->GetComponent<CompCollider>();
    if (pCollider == nullptr)
        return;

    vec2f velocity = pCollider->GetVelocity();

    HorizontalMoveState thisFrameHorizontalMoveState;
    if (Util::NearZero(velocity.x))
        thisFrameHorizontalMoveState = HorizontalMoveState::Idle;
    else if (velocity.x > 0)
        thisFrameHorizontalMoveState = HorizontalMoveState::RunRight;
    else 
        thisFrameHorizontalMoveState = HorizontalMoveState::RunLeft;

    if (thisFrameHorizontalMoveState != _lastFrameHorizontalMoveState)
    {
        _lastFrameHorizontalMoveState = thisFrameHorizontalMoveState;
        switch (thisFrameHorizontalMoveState) 
        {
        case RunLeft:
            pSpine->SetAnimation("Run", true);
            pSpine->SetFlip(false);
            break;
        case Idle:
            pSpine->SetAnimation("Wait1Loop", true);
            break;
        case RunRight:
            pSpine->SetAnimation("Run", true);
            pSpine->SetFlip(true);
            break;
        }
    }
}