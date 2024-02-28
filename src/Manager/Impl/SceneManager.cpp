#include "SceneManager.h"

void SceneManager::InitLevel() 
{
    
}

Entity* SceneManager::GetEntity(uint uid) const
{
    auto itr = _allEntitiesMap.find(uid);
    if (itr == _allEntitiesMap.end())
        return nullptr;

    return itr->second.get();
}

Entity* SceneManager::GetPlayerEntity() const 
{
    return GetEntity(_playerGuid);
}