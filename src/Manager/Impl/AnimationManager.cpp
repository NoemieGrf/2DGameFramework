#include "AnimationManager.h"
#include "../../Game/Game.h"
#include "../../Component/Impl/CompSpine.h"
#include "SceneManager.h"

void AnimationManager::Tick()
{
    SceneManager* sceneMgr = Game::GetManager<SceneManager>();
    
    for (auto& [guid, pEntity]: sceneMgr->GetSceneEntities())
    {
        CompSpine* pSpine = pEntity->GetComponent<CompSpine>();
        if (pSpine != nullptr)
            pSpine->UpdateAnimator();
    }
}

void AnimationManager::LateTick()
{
    SceneManager* sceneMgr = Game::GetManager<SceneManager>();
    float deltaTime = Game::GetDeltaTime();
    
    for (auto& [guid, pEntity]: sceneMgr->GetSceneEntities())
    {
        CompSpine* pSpine = pEntity->GetComponent<CompSpine>();
        if (pSpine != nullptr)
            pSpine->UpdateSkeletonDrawable(deltaTime);
    }
}