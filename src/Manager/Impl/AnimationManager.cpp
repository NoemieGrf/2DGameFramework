#include "AnimationManager.h"
#include "../../Game/Game.h"
#include "../../Component/Impl/CompSpine.h"
#include "../../Component/Impl/CompAnimator.h"
#include "SceneManager.h"

void AnimationManager::Tick()
{
    
}

void AnimationManager::LateTick()
{
    SceneManager* sceneMgr = Game::GetManager<SceneManager>();
    float deltaTime = Game::GetDeltaTime();
    
    for (auto& [guid, pEntity]: sceneMgr->GetSceneEntities())
    {
        // update all animator
        CompAnimator* pAnimator = pEntity->GetComponent<CompAnimator>();
        if (pAnimator != nullptr)
            pAnimator->Update();

        // update all spine
        CompSpine* pSpine = pEntity->GetComponent<CompSpine>();
        if (pSpine != nullptr)
            pSpine->UpdateSkeletonDrawable(deltaTime);
    }
}