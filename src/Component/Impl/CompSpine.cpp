#include "CompSpine.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"

void CompSpine::Load(const std::string& spineName)
{
    ResourceManager* resMgr = Game::GetManager<ResourceManager>();
    _pSpine = resMgr->CreateSpineDrawable(spineName);

    // set some default value
    spine::Skeleton* pSkeleton = _pSpine->skeleton;
    pSkeleton->setPosition(0, 0);   // bottom center
    pSkeleton->updateWorldTransform();
}

spine::SkeletonDrawable* CompSpine::GetSkeletonDrawable()
{
    return _pSpine.get();
}
